#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>
#include <limits.h>

typedef struct leaf{
    struct leaf* left;
    struct leaf* right;
    int32_t counter;
    char sign;
} leaf;

typedef struct heap{
    int32_t length;
    int32_t heap_size;
    leaf* tab;
} heap;

static inline int32_t parent(int32_t i){
    return (i - 1) / 2;
}

static inline int32_t left(int32_t i){
    return 2 * i + 1;
}

static inline int32_t right(int32_t i){
    return 2 * i + 2;
}

void swap(leaf*, leaf*);
void min_heapify(heap*, int32_t);
void build_min_heap(heap*);
leaf* heap_extract_min(heap*);
void heap_decrease_key(heap*, int32_t, leaf*, leaf, bool);
void min_heap_insert(heap*, leaf*);
void print_heap(heap*);
void free_heap(heap**);
heap* create_heap(int32_t, leaf*);
void tree_walk(leaf*, int32_t , char* , char* , char** , int32_t*);
void write_bit(FILE* file, unsigned char bit, unsigned char* buf, int32_t* bit_count);
void free_tree(leaf* node);
void decode(leaf* root, char* coded, char* decoded);

#endif
