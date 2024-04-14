#include "arena.h"

Region *region_create(size_t capacity)
{
    Region *region = malloc(sizeof(Region));
    region->capacity = capacity;
    region->alloc_pos = 0;
    region->data = malloc(sizeof(void*) * region->capacity);
    return region;
}

void *arena_alloc_aligned(Arena *arena, size_t size, size_t alignment)
{
    if (arena->head == NULL && arena->tail == NULL) {
        Region *r = region_create(ARENA_CMP(size));
        arena->head = r;
        arena->tail = r;
    }

    Region *cur = arena->head;
    while (1) {
        if (cur->alloc_pos + size > cur->capacity) {
            if (cur->next != NULL) {
                cur = cur->next;
                continue;
            } else {
                Region *r = region_create(ARENA_CMP(size));
                arena->tail->next = r;
                arena->tail = r;
                cur = arena->tail;
                continue;
            }
        } else {
            size_t align_size = ARENA_ALIGN(size, alignment);
            void *ptr = (void*)(cur->data + cur->alloc_pos + align_size);
            cur->alloc_pos += align_size;
            return ptr;
        }
    }
}

void *arena_alloc(Arena *arena, size_t size)
{
    return arena_alloc_aligned(arena, size, sizeof(void*));
}

void *arena_realloc(Arena *arena, void *old_ptr, size_t old_size, size_t new_size)
{
    if (new_size > old_size) {
        void *new_ptr = arena_alloc(arena, new_size);
        memcpy(new_ptr, old_ptr, old_size);
        return new_ptr;
    } else {
        return old_ptr;
    }
}

void arena_dump(Arena *arena)
{
    size_t i = 1;
    Region *cur = arena->head;
    while (cur != NULL) {
        printf("region %zu: %zu/%zu\n", i, cur->alloc_pos, cur->capacity);
        i += 1;
        cur = cur->next;
    }
}

void arena_reset(Arena *arena)
{
    Region *cur = arena->head;
    while (cur != NULL) {
        cur->alloc_pos = 0;
        cur = cur->next;
    }
}

void arena_free(Arena *arena)
{
    Region *cur = arena->head;
    while (cur != NULL) {
        Region *next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
    }
}