#include "arena.h"

// Test data strcuter for arena
typedef struct foo {
    struct foo* next;
    int data;
} Foo;

typedef struct {
    Foo *head;
    Foo *tail;
    size_t count;
} Foo_List;

void foo_push(Arena *arena, Foo_List* list, int data)
{
    Foo *fo = arena_alloc(arena, sizeof(Foo));
    fo->data = data;
    fo->next = NULL;

    if (!list->tail) {
        list->head = fo;
        list->tail = fo;
        list->count += 1;
    } else {
        list->tail->next = fo;
        list->tail = fo;
        list->count += 1;
    }
}

void foo_print(Foo_List* list)
{
    Foo *cur = list->head;
    while (cur != NULL) {
        printf("data: %d\n", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

// Test foo
void test0()
{
    Arena arena = {0};

    Foo_List foo = {0};

    foo_push(&arena, &foo, 12);
    foo_push(&arena, &foo, 122);
    foo_push(&arena, &foo, 1);
    foo_push(&arena, &foo, 13);
    foo_push(&arena, &foo, 1765);
    foo_push(&arena, &foo, 16);
    foo_push(&arena, &foo, 11);
    foo_print(&foo);

    arena_dump(&arena);
    arena_free(&arena);
}

// Test arena_realloc
void test1()
{
    Arena arena = {0};
    const size_t N = 1234;
    
    void *p = arena_alloc(&arena, N);
    p = arena_realloc(&arena, p, N, 3456);

    arena_dump(&arena);
    arena_free(&arena);
}

int main()
{
    test1();
    return 0;
}