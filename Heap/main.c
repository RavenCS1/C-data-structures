#include "heap.h"

jmp_buf env;

void catcher(void){
    longjmp(env, 1);
}

int main(void){
    srand(time(0));

    int32_t n;

    // I am aware of the fact that longjump is a serious overkill here.
    // However I was curious and wanted to see how it works.

    if(setjmp(env))
        (void) printf("Size of the heap should be > 0!\n\n");
    do{
        (void) printf("Please input size of the heap which you would like to create(> 0): ");
        scanf("%" SCNd32, &n);
        if(n <= 0)
            catcher();
    } while(n <= 0);

    heap* handle = create_heap(n);
    (void) printf("\n\nRandomly created heap:\n\n");
    print_heap(handle);

    build_min_heap(handle);
    (void) printf("Properly built heap:\n\n");
    print_heap(handle);

    int32_t min = heap_extract_min(handle);
    (void) printf("Minimal value of the heap = %" PRId32 "\n\nHeap after extraction of minimal value\n\n", min);
    print_heap(handle);

    heap_decrease_key(handle, handle -> heap_size - 1, min, handle -> tab[handle -> heap_size - 1], false);
    (void) printf("After decreasing key of the last element of the heap:\n\n");
    print_heap(handle);

    min_heap_insert(handle, 0);
    min_heap_insert(handle, -1);
    (void) printf("After inserting to elements with lower value of their keys:\n\n");
    print_heap(handle);

    heapsort(handle);
    (void) printf("Heap after it was sorted with heapsort algorithm:\n\n");
    print_heap(handle);

    reverse(handle);
    (void) printf("Reversed heap:\n\n");
    print_heap(handle);

    free_heap(&handle);
    return EXIT_SUCCESS;
}



