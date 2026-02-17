#include "huffman.h"

int main(int argc, char* argv[argc + 1]){
    if(argc != 2){
        (void) printf("Inappropriate usage of the program!\n");
        (void) printf("Appropriate usage: ./Huffman_coding input.txt\n\n");
        exit(EXIT_FAILURE);
    }

    char* input_file = argv[1];
    char* output_binary = "output.bin";
    char* output_file = "output.txt";

    FILE* input = fopen(input_file, "r");
    if(!input){
        (void) printf("Error - it was not possible to open the input txt file to encryption!\n\n");
        exit(EXIT_FAILURE);
    }

    int32_t n = 0;
    bool flag = false;
    char character;
    leaf* tab = nullptr;

    while((character = getc(input)) != EOF){
        flag = false;
        for(int32_t i = 0; i < n; ++i){
            if(tab[i].sign == character){
                tab[i].counter += 1;
                flag = true;
                break;
            }
        }
        if(!flag){
            n++;
            tab = realloc(tab, n * sizeof(tab[0]));
            tab[n - 1] = (leaf){nullptr, nullptr, 1, character};
        }
    }

    heap* handle = create_heap(n, tab);
    (void) printf("At the beginning:\n\n");
    print_heap(handle);

    build_min_heap(handle);
    (void) printf("Properly built heap:\n\n");
    print_heap(handle);

    leaf* x, *y, *z;
    x = y = z = nullptr;

    for(int32_t i = 1; i < n; ++i){
        z = malloc(sizeof(*z));
        if(!z){
            (void) printf("Allocation of a new leaf in a greedy algorithm was unfortunately unsucessful!\n\n");
            exit(EXIT_FAILURE);
        }
        x = heap_extract_min(handle);
        y = heap_extract_min(handle);
        z -> left = x;
        z -> right = y;
        z -> counter = x -> counter + y -> counter;
        z -> sign = '.';
        min_heap_insert(handle, z);
        free(z);
    }

    z = heap_extract_min(handle);
    free_heap(&handle);

    char tabsign[n];
    char** tabcodes = malloc(n * sizeof(char*));
    for(int32_t i = 0; i < n; ++i)
        tabcodes[i] = malloc(sizeof(char[n + 1]));

    char buffer[n + 1];
    int32_t idx = 0;

    tree_walk(z, 0, buffer, tabsign, tabcodes, &idx);
    for(int32_t i = 0; i < n; ++i){
        if(tabsign[i] != '\n') (void) printf("Letter: %c ", tabsign[i]);
        else (void) printf("Letter: \\n ");
        (void) printf("Generated encryption: %s\n", tabcodes[i]);
    }

    FILE* output = fopen(output_binary, "wb");
    if(!output){
        (void) printf("Error - it was not possible to open the binary file to write the encryption!\n\n");
        exit(EXIT_FAILURE);
    }

    rewind(input);
    fseek(input, 0, SEEK_END); // somewhere I read that SEEK_END macro has a glitch and can impose some problems
    int32_t input_length = ftell(input);
    rewind(input);
    fwrite(&input_length, sizeof(int32_t), 1, output);

    int32_t id;
    char* code = nullptr;
    unsigned char buf = 0;
    int32_t bit_count = 0;
    unsigned char bit;

    while((character = getc(input)) != EOF){
        id = -1;
        for(int32_t k = 0; k < n; ++k){
            if(tabsign[k] == character){ 
                id = k; 
                break; 
            }
        }
        code = tabcodes[id];
        for(int32_t j = 0; code[j] != '\0'; ++j){
            bit = code[j] - '0';
            write_bit(output, bit, &buf, &bit_count);
        }
    }

    if(bit_count > 0){
        buf <<= (8 - bit_count);
        fwrite(&buf, 1, 1, output);
    }

    fclose(input);
    fclose(output);

    decode(z, output_binary, output_file);

    for(int32_t i = 0; i < n; ++i)
        free(tabcodes[i]);

    free(tabcodes);
    free_tree(z);

    return EXIT_SUCCESS;
}
