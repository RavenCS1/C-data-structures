#include "heap.h"

void swap(int32_t* a, int32_t* b){
    int32_t tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void min_heapify(heap* handle, int32_t i){
    int32_t l = left(i);
    int32_t r = right(i);
    int32_t smallest;
    if((l < handle -> heap_size) && (handle -> tab[l] < handle -> tab[i])) smallest = l;
    else smallest = i;
    if((r < handle -> heap_size) && (handle -> tab[r] < handle -> tab[smallest])) smallest = r;
    if(smallest != i){
       swap(&(handle -> tab[i]), &(handle -> tab[smallest]));
       min_heapify(handle, smallest);
    }
    return;
}

void build_min_heap(heap* handle){
    handle -> heap_size = handle -> length;
    for(int32_t i = handle -> length / 2 - 1; i >= 0; --i)
        min_heapify(handle, i);
    return;
}

void heapsort(heap* handle){
    build_min_heap(handle);
    for(int32_t i = (handle -> length) - 1; i >= 1; --i){
        swap(&(handle -> tab[0]), &(handle -> tab[i]));
        handle -> heap_size -= 1;
        min_heapify(handle, 0);
    }
    handle -> heap_size = handle -> length;
    return; 
}
void reverse(heap* handle){
    for(int32_t i = 0; i < handle -> length / 2; ++i)
        swap(&(handle -> tab[i]), &(handle-> tab[handle -> length - 1 - i]));
}

int32_t heap_minimum(heap* handle){
    return handle -> tab[0];
}

int32_t heap_extract_min(heap* handle){
    if(handle -> heap_size < 1){
        (void) printf("Error - heap is currently empty!\n\n");
        return -1;
    }
    int32_t min = handle -> tab[0];
    handle -> tab[0] = handle -> tab[handle -> heap_size - 1];
    handle -> heap_size -= 1;
    min_heapify(handle, 0);
    return min;
}

void heap_decrease_key(heap* handle, int32_t i, int32_t key, int32_t old, bool changed){
    if(key > handle -> tab[i]){
        (void) printf("A new key is bigger than the current key!\n\n");
        if(!changed)
            handle -> tab[handle -> heap_size - 1] = old;
        else{
            handle -> length -= 1;
            handle -> heap_size -= 1;
            handle -> tab = realloc(handle -> tab, (handle -> heap_size) * sizeof((handle -> tab)[0]));
        }
        return;
    }
    handle -> tab[i] = key;
    while(i > 0 && handle -> tab[parent(i)] > handle -> tab[i]){
        swap(&(handle -> tab[i]), &(handle -> tab[parent(i)]));
        i = parent(i);
    }
    return;
}

void min_heap_insert(heap* handle, int32_t key){
    handle -> heap_size += 1;
    bool changed = false;
    if(handle -> heap_size > handle -> length){
        changed = true;
        handle -> tab = realloc(handle -> tab, (handle -> heap_size) * sizeof((handle -> tab)[0]));
        if(!(handle -> tab)){
            (void) printf("Error - extention of the heap was unfortunately unsuccesful!\n");
            exit(EXIT_FAILURE);
        }
        handle -> length = handle -> heap_size;
    }
    int32_t old;
    if(!changed) old = handle -> tab[handle -> heap_size - 1];
    else old = -1;
    handle -> tab[handle -> heap_size - 1] = INT32_MAX; 
    heap_decrease_key(handle, handle -> heap_size - 1, key, old, changed);
    return;
}

void print_heap(heap* handle){
    (void) printf("Current status of the heap:\n\n");
    (void) printf("Length: %" PRId32 "\n", handle -> length);
    (void) printf("Heap_size: %" PRId32 "\n\n", handle -> heap_size);
    (void) printf("Whole table:\n");
    for(int32_t i = 0; i < handle -> length; ++i)
        (void) printf("tab[%" PRId32 "] = %" PRId32 "\n", i, handle -> tab[i]);
    (void) printf("\nHeap only:\n");
    for(int32_t i = 0; i < handle -> heap_size; ++i)
        (void) printf("tab[%" PRId32 "] = %" PRId32 "\n", i, handle -> tab[i]);
    (void) printf("\n");
    return;
}

void free_heap(heap** handle_address){
    (void) printf("Deallocation of the heap!\n\n");
    free((*handle_address) -> tab);
    free(*handle_address);
    return;
}

heap* create_heap(int32_t n){
    heap* handle = malloc(sizeof(*handle));
    if(!handle){
        (void) printf("Allocation of the heap handle was unfortunately unsuccesful!\n\n");
        exit(EXIT_FAILURE);
    }
    handle -> length = n;
    handle -> heap_size = n;
    handle -> tab = malloc(sizeof(int32_t[n]));
    if(!(handle -> tab)){
        (void) printf("Allocation of the heap was unfortunately unsuccesful!\n\n");
        exit(EXIT_FAILURE);
    }
    for(int32_t i = 0; i < n; ++i)
        handle -> tab[i] = rand_int32_t(1, n);
    return handle;
}

