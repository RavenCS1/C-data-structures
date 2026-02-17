#include "tree.h"

void print_leaf(node* x){
    if(x){
        (void) printf("Adress of the node: %p\n", (void *)x);
        (void) printf("Value of the key: %" PRId32 "\n", x -> key);
        (void) printf("Adress of the parent: %p\n", (void *)(x -> parent));
        (void) printf("Adress of the left son: %p\n", (void *)(x -> left));
        (void) printf("Adress of the right son: %p\n\n", (void *)(x -> right));
    }
    else (void) printf("Invalid pointer! Couldn't print out pieces of information about a node.\n");
    return;
}

void inorder_tree_walk(node* x){
    if(x){
        inorder_tree_walk(x -> left);
        print_leaf(x);
        inorder_tree_walk(x -> right);
    }
    return;
}

void preorder_tree_walk(node* x){
    if(x){
        print_leaf(x);
        preorder_tree_walk(x -> left);
        preorder_tree_walk(x -> right);
    }
    return;
}

void postorder_tree_walk(node* x){
    if(x){
        postorder_tree_walk(x -> left);
        postorder_tree_walk(x -> right);
        print_leaf(x);
    }
    return;
}

node* tree_search(node* x, int32_t k){
    if(x || k == x -> key) return x;
    if(k < x -> key) return tree_search(x -> left, k);
    else return tree_search(x -> right, k);
}


node* iterative_tree_search(node* x, int32_t k){
    while(x && k != x -> key){
        if(k < x -> key) x = x -> left;
        else x = x -> right;
   }
   return x;
}

node* tree_minimum(node* x){
    while(x -> left) x = x -> left;
    return x;
}

node* tree_maximum(node* x){
    while(x -> right) x = x -> right;
    return x;
}

node* tree_successor(node* x){
    if(x -> right) return tree_minimum(x -> right);
    node* y = x -> parent;
    while(y && x == y -> right){
        x = y;
        y = y -> parent;
    }
    return y;
}

node* tree_predecessor(node* x){
    if(x -> left) return tree_maximum(x -> left);
    node* y = x -> parent;
    while(y && x == y -> left){
        x = y;
        y = y -> parent;
    }
    return y;
}


node* create(int32_t k){
    node* new = malloc(sizeof(*new));
    if(!new){
        (void) printf("Allocation of a new node was unfortunately unsuccesful!\n");
        exit(EXIT_FAILURE);
    }
    new -> key = k;
    new -> parent = new -> left = new -> right = nullptr;
    return new;
}

void tree_insert(node** root, node* z){
    node* y = nullptr;
    node* x = *root;
    while(x){
        y = x;
        if(z -> key < x -> key) x = x -> left;
        else x = x -> right;
    }
    z -> parent = y;
    if(!y) *root = z;
    else if(z -> key < y -> key) y -> left = z;
    else y -> right = z;
    return;
}

void transplant(node** root, node* u, node* v){
    if(!(u -> parent)) *root = v;
    else if(u == u -> parent -> left) u -> parent -> left = v;
    else u -> parent -> right = v;
    if(v) v -> parent = u -> parent;
    return;
}

void tree_delete(node** root, node* z){
    if(!(z -> left)) transplant(root, z, z -> right);
    else if(!(z -> right)) transplant(root, z, z -> left);
    else{
        node* y = tree_minimum(z -> right);
        if(y -> parent != z){
            transplant(root, y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        }
        transplant(root, z, y);
        y -> left = z -> left;
        y -> left -> parent = y;
    }
    z -> left = z -> right = z -> parent = nullptr;
    free(z);
    return;
}

void free_tree(node** root){ 
    node* x = *root;
    node* min = nullptr;
    node* max = nullptr;
    while(((min = tree_minimum(x)) != x) && min){
        (void) printf("Dealocation of a node:\n");
        print_leaf(min);
        min -> parent -> left = min -> right;
        if(min -> right) min -> right -> parent = min -> parent;
        memset(min, 0, sizeof(*min));
        free(min);
    }
    while(((max = tree_maximum(x)) != x) && max){
        (void) printf("Dealocation of a node:\n");
        print_leaf(max);
        max -> parent -> right = max -> left;
        if(max -> left) max -> left -> parent = max -> parent;
        memset(max, 0, sizeof(*max));
        free(max);
    }
    (void) printf("Dealocation of a node:\n");
    print_leaf(x);
    memset(x, 0, sizeof(*x));
    free(x);
    *root = nullptr;
    return;
}
