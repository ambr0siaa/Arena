#include "arena.h"

// Test data structure for arenastruct 
typedef struct Tree Tree;

struct Tree {
    char data;
    Tree *left;
    Tree *right;
};

Tree *generate_tree(Arena *arena, size_t level_cur, size_t level_max)
{
    if (level_cur < level_max) {
        Tree *tree = arena_alloc(arena, sizeof(Tree));
        tree->data = level_cur + 'a'; 
        tree->left = generate_tree(arena, level_cur + 1, level_max);
        tree->right = generate_tree(arena, level_cur + 1, level_max);
        return tree;
    } else {
        return NULL;
    }
}

#define TAB(iter)                            \
    do {                                     \
        for (size_t j = 0; j < (iter); ++j)  \
            printf("    ");                  \
    } while (0)

void tree_dump(Tree *tree, size_t level)
{
    if (level == 0)
        printf("root: '%c'\n", tree->data);

    if (tree->right) {
        TAB(level + 1);
        printf("right: '%c'\n", tree->right->data);
        tree_dump(tree->right, level + 1);
    }

    if (tree->left) {
        TAB(level + 1);
        printf("left: '%c'\n", tree->left->data);
        tree_dump(tree->left, level + 1);
    }
}

// Test data structure
void test0()
{
    Arena arena = {0};
    Tree *tree = generate_tree(&arena, 0, 4);
    tree_dump(tree, 0);
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
    test0();
    return 0;
}