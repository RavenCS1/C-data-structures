#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef struct tnode{       
	int32_t value;
    struct tnode *prev;
    struct tnode *next;
} node;

static inline int32_t rand_int32_t(int32_t a, int32_t b){
    return (a + rand() % (b - a + 1));
}

node* create(int32_t);
void print_node(node*);
void print_list_next(node*);
void print_list_prev(node*);
node* add_first(node*, node*);
node* add_last(node*, node*);
node* pull_all_elements(node**, int32_t);
node* pull_one_element(node**, int32_t);
void add_sort(node**, node*);
void sort_divided(node**);
void sort_reversed_divided(node**);
void sort(node**);
void free_list(node**);

#endif
