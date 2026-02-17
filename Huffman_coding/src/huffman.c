#include "huffman.h"

void swap(leaf* a, leaf* b){
    leaf tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void min_heapify(heap* handle, int32_t i){
    int32_t l = left(i);
    int32_t r = right(i);
    int32_t smallest;
    if((l < handle -> heap_size) && (handle -> tab[l].counter < handle -> tab[i].counter)) smallest = l;
    else smallest = i;
    if((r < handle -> heap_size) && (handle -> tab[r].counter < handle -> tab[smallest].counter)) smallest = r;
    if(smallest != i){
       swap(&(handle -> tab[i]), &(handle -> tab[smallest]));
       min_heapify(handle, smallest);
    }
    return;
}

void build_min_heap(heap* handle){
    handle -> heap_size = handle -> length;
    for(int32_t i = handle -> length / 2 - 1; i >= 0; i--)
        min_heapify(handle, i);
    return;
}

leaf* heap_extract_min(heap* handle){
    leaf* tmp = nullptr;
    if(handle -> heap_size < 1){
        (void) printf("Error - heap is currently empty!\n\n");
        tmp = malloc(sizeof(*tmp));
        if(!tmp){
            (void) printf("Allocation of an empty leaf was unfortunately unsucesful!\n\n");
            exit(EXIT_FAILURE);
        }
        *tmp = (leaf){nullptr, nullptr, 0, '.'};
        return tmp;
    }
    leaf min = handle -> tab[0];
    tmp = malloc(sizeof(*tmp));
    if(!tmp){
        (void) printf("Allocation of a new leaf was unfortunately unsucesful!\n\n");
        exit(EXIT_FAILURE);
    }
    *tmp = min;
    handle -> tab[0] = handle -> tab[handle -> heap_size - 1];
    handle -> heap_size -= 1;
    min_heapify(handle, 0);
    return tmp;
}

void heap_decrease_key(heap* handle, int32_t i, leaf* key, leaf old, bool changed){
    if(key -> counter > handle -> tab[i].counter){
        (void) printf("A new key is bigger than the current one!\n\n");
        if(!changed)
            handle -> tab[handle -> heap_size - 1] = old;
        else{
            handle -> length -= 1;
            handle -> heap_size -= 1;
            handle -> tab = realloc(handle -> tab, (handle -> heap_size) * sizeof(*(handle -> tab)));
        }
        return;
    }
    handle -> tab[i] = *key;
    while(i > 0 && handle -> tab[parent(i)].counter > handle -> tab[i].counter){
        swap(&(handle -> tab[i]), &(handle -> tab[parent(i)]));
        i = parent(i);
    }
    return;
}

void min_heap_insert(heap* handle, leaf* key){
    handle -> heap_size += 1;
    bool changed = false;
    if(handle -> heap_size > handle -> length){
        changed = true;
        handle -> tab = realloc(handle -> tab, (handle -> heap_size) * sizeof((handle -> tab)[0]));
        if(!(handle -> tab)){
            (void) printf("Error - extention of the heap was unfortunately unsuccesful!\n\n");
            exit(EXIT_FAILURE);
        }
        handle -> length = handle -> heap_size;
    }
    leaf old;
    if(!changed)
        old = handle -> tab[handle -> heap_size - 1];
    else{
        old.left = old.right = nullptr;
        old.counter = 0;
        old.sign = '.';
    }
    handle -> tab[handle -> heap_size - 1] = (leaf){nullptr, nullptr, INT32_MAX, '.'};
    heap_decrease_key(handle, handle -> heap_size - 1, key, old, changed);
    return;
}

void print_heap(heap* handle){
    (void) printf("Length: %" PRId32 "\n", handle -> length);
    (void) printf("Heap_size: %" PRId32 "\n\n", handle -> heap_size);
    (void) printf("Whole table:\n\n");
    for(int32_t i = 0; i < handle -> length; ++i){
        (void) printf("\ntab[%" PRId32 "]:\n", i);
        if(handle -> tab[i].sign != '\n') (void) printf("Letter: %c\n", handle -> tab[i].sign);
        else (void)printf("Letter: \\n\n");
        (void) printf("Number of occurences: %" PRId32 "\n", handle -> tab[i].counter);
    }
    (void) printf("\nHeap only:\n");
    for(int32_t i = 0; i < handle -> heap_size; ++i){
        (void) printf("\ntab[%" PRId32"]:\n", i);
        if(handle -> tab[i].sign != '\n') (void) printf("Letter: %c\n", handle -> tab[i].sign);
        else (void) printf("Letter: \\n\n");
        (void) printf("Number of occurences: %d\n", handle -> tab[i].counter);
    }
    (void) printf("\n");
    return;
}

void free_heap(heap** handle_adress){
    (void) printf("Deallocation of the heap!\n\n");
    free((*handle_adress) -> tab);
    free(*handle_adress);
    *handle_adress = nullptr;
    return;
}

heap* create_heap(int32_t n, leaf* tab){
    heap* handle = malloc(sizeof(*handle));
    if(!handle){
        (void) printf("Allocation of handle for the heap was unfortunately unsucessful!\n\n");
        exit(EXIT_FAILURE);
    }
    handle -> length = n;
    handle -> heap_size = n;
    handle -> tab = tab;
    return handle;
}

void tree_walk(leaf* node, int32_t depth, char* buffer, char* tabsign, char** tabcodes, int32_t* ptridx){
    if(!node) return;
    if(!(node -> left) && !(node -> right)){
        buffer[depth] = '\0';
        tabsign[*ptridx] = node -> sign;
        strcpy(tabcodes[*ptridx], buffer);
        (*ptridx)++;
    }
    else{
        if(node -> left){
            buffer[depth] = '0';
            tree_walk(node -> left, depth + 1, buffer , tabsign, tabcodes, ptridx);
        }
        if(node -> right){
            buffer[depth] = '1';
            tree_walk(node -> right, depth + 1, buffer , tabsign, tabcodes, ptridx);
        }
    }
}

void write_bit(FILE* file, unsigned char bit, unsigned char* buf, int32_t* bit_count){
    *buf = (*buf << 1) | (bit & 1);
    (*bit_count)++;
    if(*bit_count == 8){
        fwrite(buf, 1, 1, file);
        *bit_count = 0;
        *buf = 0;
    }
}

void free_tree(leaf* root){
    if(!root) return;
    free_tree(root -> left);
    free_tree(root -> right);
    free(root);
}

void decode(leaf* root, char* coded, char* decoded){
    FILE* fcoded = fopen(coded, "rb");
    if(!fcoded){
        (void) printf("Error - it was not possible to open the binary file to decoding!\n\n");
        exit(EXIT_FAILURE);
    }
    FILE* fdecoded = fopen(decoded, "w");
    if(!fdecoded){
        (void) printf("Error - it was not possible to open the txt file to decoding!\n\n");
        exit(EXIT_FAILURE);
    }
    int32_t input_length = 0;
    fread(&input_length, sizeof(int32_t), 1, fcoded);
    int32_t decoded_count = 0;
    leaf* current = root;
    int32_t byte, bit;
    while(decoded_count < input_length && (byte = getc(fcoded)) != EOF){
        for(int32_t bit_pos = 7; bit_pos >= 0; --bit_pos){
            bit = (byte >> bit_pos) & 1;
            if(!bit) current = current -> left;
            else current = current -> right;
            if(!current){
                (void) printf("Unexpected error of decoding occured!\n\n");
                fclose(fcoded);
                fclose(fdecoded);
                return;
            }
            if(!(current -> left) && !(current -> right)){
                fputc(current -> sign, fdecoded);
                current = root;
                decoded_count++;
                if(decoded_count == input_length) break;
            }
        }
    }
    fclose(fcoded);
    fclose(fdecoded);
    return;
}
