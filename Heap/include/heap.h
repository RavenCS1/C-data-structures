#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <math.h>
#include <limits.h>
#include <setjmp.h>

typedef struct heap{
    int32_t length;
    int32_t heap_size;
    int32_t* tab;
} heap;

static inline int32_t rand_int32_t(int32_t a, int32_t b){
    return (a + rand() % (b - a + 1));
}

static inline int32_t parent(int32_t i){
    return (i - 1) / 2;
}

static inline int32_t left(int32_t i){
    return 2 * i + 1;
}

static inline int32_t right(int32_t i){
    return 2 * i + 2;
}

void swap(int32_t*, int32_t*);
void min_heapify(heap*, int32_t);
void build_min_heap(heap*);
void heapsort(heap*);
void reverse(heap*);
int32_t heap_minimum(heap*);
int32_t heap_extract_min(heap*);
void heap_decrease_key(heap*, int32_t, int32_t, int32_t, bool);
void min_heap_insert(heap*, int32_t);
void print_heap(heap*);
void free_heap(heap**);
heap* create_heap(int32_t);

#endif
