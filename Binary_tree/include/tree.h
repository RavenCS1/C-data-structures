#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

#define N ((int32_t) 6)

typedef struct tnode{
    int32_t key;
    struct tnode* parent;
    struct tnode* left;
    struct tnode* right;
} node;

static inline int32_t rand_int32_t(int32_t a, int32_t b){
    return (a + rand() % (b - a + 1));
}

void print_leaf(node*);
void inorder_tree_walk(node*);
void preorder_tree_walk(node*);
void postorder_tree_walk(node*);
node* tree_search(node*, int32_t);
node* iterative_tree_search(node*, int32_t);
node* tree_minimum(node*);
node* tree_maximum(node*);
node* tree_successor(node*);
node* tree_predecessor(node*);
node* create(int32_t);
void tree_insert(node**, node*);
void transplant(node**, node*, node*);
void tree_delete(node**, node*);
void free_tree(node**);

#endif
