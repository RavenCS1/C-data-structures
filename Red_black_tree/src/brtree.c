#include "brtree.h"

leaf* allocate_leaf(int32_t key){
    leaf* new_leaf = malloc(sizeof(*new_leaf));
    if(!new_leaf){
        (void) printf("Allocation of a new leaf was unfortunately unsucessful!\n\n");
        exit(EXIT_FAILURE);
    }
    new_leaf -> value = key;
    new_leaf -> parent = new_leaf -> left = new_leaf -> right = nullptr;
    return new_leaf;
}

holder* allocate_holder(void){
    holder* tree = malloc(sizeof(*tree));
    if(!tree){
        (void) printf("Allocation of a handle for the tree was unfortunately unsucessful!\n\n");
        exit(EXIT_FAILURE);
    }
    tree -> root = nullptr;
    leaf* sentinel = allocate_leaf(-1);
    tree -> guard = sentinel;
    tree -> guard -> color = BLACK;
    tree -> guard -> parent = tree -> guard;
    tree -> guard -> left = tree -> guard -> right = tree -> guard;
    return tree;
}

void free_tree(holder* tree, leaf* x){
    if(x != tree -> guard){            
        free_tree(tree, x -> left);
        free_tree(tree, x -> right);
        free(x);
    }
    return;
}

void free_holder(holder** handle_address){
    free((*handle_address) -> guard);
    free(*handle_address);
    *handle_address = nullptr;
    return;
}

void inorder_tree_walk(holder* tree, leaf* x){
    if(x != tree -> guard){
        inorder_tree_walk(tree, x -> left);
        printf("Wartość w węźle: %d\n", x -> value);
        printf("Kolor węzła (0 - BLACK, 1 - RED): %d\n", x -> color);
        printf("Adres węzła: %p\n", (void *)(x));
        printf("Adres rodzica węzła: %p\n", (void *)(x -> parent));
        printf("Adres lewego syna węzła:%p\n", (void *)(x -> left));
        printf("Adres prawego syna węzła: %p\n\n", (void *)(x -> right));
        inorder_tree_walk(tree, x -> right);
    }
    return;
}

void preorder_tree_walk(holder* tree, leaf* x){
    if(x != tree -> guard){
        print_leaf(tree, x);
        preorder_tree_walk(tree, x -> left);
        preorder_tree_walk(tree, x -> right);
    }
    return;
}

void postorder_tree_walk(holder* tree, leaf* x){
    if(x != tree -> guard){
        postorder_tree_walk(tree, x -> left);
        postorder_tree_walk(tree, x -> right);
        print_leaf(tree, x);
    }
    return;
}

void print_leaf(holder* tree, leaf* x){
    if(x != tree -> guard){
        (void) printf("Adress of the leaf: %p\n", (void *)(x));
        (void) printf("Adress of the parent of the leaf: %p\n", (void *)(x -> parent));
        (void) printf("Adress of the left son of the leaf: %p\n", (void *)(x -> left));
        (void) printf("Adress of the right son of the leaf: %p\n\n", (void *)(x -> right));
        (void) printf("Value of the key in the leaf: %" PRId32 "\n", x -> value);
        (void) printf("Color of the leaf (0 - black, 1 - red): %" PRId8 "\n", x -> color);
    }
    return;
}

void prit_holder(holder* tree){
    (void) printf("Adress of the root of the Red-black tree: %p\n", (void *)(tree -> root));
    (void) printf("Adress of the sentinel of the three: %p\n", (void *)(tree -> guard));
    (void) printf("Number of leaves in the Red-black tree: %" PRId32 "\n\n", tree -> number_of_elem);
    return;
}

leaf* tree_search(holder* tree, leaf* x, int32_t k){
    if(x != tree -> guard || k == x -> value) return x;
    if(k < x -> value) return tree_search(tree, x -> left, k);
    else return tree_search(tree, x -> right, k);
}

leaf* iterative_tree_search(holder* tree, leaf* x, int32_t k){
    while(x != tree -> guard && k != x -> value){
        if(k < x -> value) x = x -> left;
        else x = x -> right;
   }
   return x;
}

leaf* tree_minimum(holder* tree, leaf* x){
    while(x -> left != tree -> guard)
        x = x -> left;
    return x;
}

leaf* tree_maximum(holder* tree, leaf* x){
    while(x -> right != tree -> guard)
        x = x -> right;
    return x;
}

leaf* tree_successor(holder* tree, leaf* x){
    if(x -> right != tree -> guard) return tree_minimum(tree, x -> right);
    leaf* y = x -> parent;
    while(y != tree -> guard && x == y -> right){
        x = y;
        y = y -> parent;
    }
    return y;
}

leaf* tree_predecessor(holder* tree, leaf* x){
    if(x -> left != tree -> guard) return tree_maximum(tree, x -> left);
    leaf*  y = x -> parent;
    while(y != tree -> guard && x == y -> left){
        x = y;
        y = y -> parent;
    }
    return y;
}

void right_rotate(holder* tree, leaf* x){
    leaf* y = x -> left;
    x -> left = y -> right;
    if(y -> right != tree -> guard) y -> right -> parent = x;
    y -> parent = x -> parent;
    if(x -> parent == tree -> guard) tree -> root = y;
    else if(x == x -> parent -> right) x -> parent -> right = y;
    else x -> parent -> left = y;
    y -> right = x;
    x -> parent = y;
    return;
}

void left_rotate(holder* tree, leaf* x){
    leaf* y = x -> right;
    x -> right = y -> left;
    if(y -> left != tree -> guard) y -> left -> parent = x;
    y -> parent = x -> parent;
    if(x -> parent == tree -> guard) tree -> root = y;
    else if(x == x -> parent -> left) x -> parent -> left = y;
    else x -> parent -> right = y;
    y -> left = x;
    x -> parent = y;
    return;
}

void rb_insert(holder* tree, leaf* z){
    leaf* y = tree -> guard;
    leaf* x = tree -> root;
    while(x != tree -> guard){
        y = x;
        if(z -> value < x -> value) x = x -> left;
        else x = x -> right;
    }
    z -> parent = y;
    if(y == tree -> guard) tree -> root = z;
    else if(z -> value < y -> value) y -> left = z;
    else y -> right = z;
    z -> left = tree -> guard;
    z -> right = tree -> guard;
    z -> color = RED;
    rb_insert_fixup(tree, z);
    tree -> number_of_elem += 1;
    return;
}

void rb_insert_fixup(holder* tree,  leaf* z){
    leaf* y = nullptr;
    while(z -> parent -> color == RED){
        if(z -> parent == z -> parent -> parent -> left){
            y = z -> parent -> parent -> right;
            if(y -> color == RED){
                z -> parent -> color = BLACK;
                y -> color = BLACK;
                z -> parent -> parent -> color = BLACK;
                z = z -> parent -> parent;
            }
            else{
                if(z == z -> parent -> right){
                    z = z -> parent;
                    left_rotate(tree, z);
                }
                z -> parent -> color = BLACK;
                z -> parent -> parent -> color = RED;
                right_rotate(tree, z -> parent -> parent);
            }
        }
        else{
            y = z -> parent -> parent -> left;
            if(y -> color == RED){
                z -> parent -> color = BLACK;
                y -> color = BLACK;
                z -> parent -> parent -> color = BLACK;
                z = z -> parent -> parent;
            }
            else{
                if(z == z -> parent -> left){
                    z = z -> parent;
                    right_rotate(tree, z);
                }
                z -> parent -> color = BLACK;
                z -> parent -> parent -> color = RED;
                left_rotate(tree, z -> parent -> parent);
            }
        }
    }
    tree -> root -> color = BLACK;
    return;
}

void rb_transplant(holder* tree, leaf* u, leaf* v){
    if(u -> parent == tree -> guard) tree -> root = v;
    else if(u == u -> parent -> left) u -> parent -> left = v;
    else u -> parent -> right = v;
    v -> parent = u -> parent;
    return;
}

void rb_delete(holder* tree, leaf* z){
    leaf* y = z;
    leaf* x = nullptr;
    int32_t original_color = y -> color;
    if(z -> left == tree -> guard){
        x = z -> right;
        rb_transplant(tree, z, z -> right);
    }
    else if(z -> right == tree -> guard){
        x = z -> left;
        rb_transplant(tree, z, z -> left);
    }
    else{
        y = tree_minimum(tree, z -> right);
        original_color = y -> color;
        x = y -> right;
        if(y -> parent == z) x -> parent = y;
        else{
            rb_transplant(tree, y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        }
        rb_transplant(tree, z, y);
        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
    }
    free(z);
    if(original_color == BLACK) rb_delete_fixup(tree, x);
    tree -> number_of_elem -= 1;
    return;
}

void rb_delete_fixup(holder* tree, leaf* x){
    leaf* w = nullptr;
    while(x != tree -> guard && x -> color == BLACK){
        if(x == x -> parent -> left){
            w = x -> parent -> right;
            if(w -> color == RED){
                w -> color = BLACK;
                x -> parent -> color = RED;
                left_rotate(tree, x -> parent);
                w = x -> parent -> right;
            }
            if(w -> left -> color == BLACK && w -> right -> color == BLACK){
                w -> color = RED;
                x = x -> parent;
            }
            else{
                if(w -> right -> color == BLACK){
                    w -> left -> color = BLACK;
                    w -> color = RED;
                    right_rotate(tree, w);
                    w = x -> parent -> right;
                }
                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> right -> color = BLACK;
                left_rotate(tree, x -> parent);
                x = tree -> root;
            }
        }
        else{
            w = x -> parent -> left;
            if(w -> color == RED){
                w -> color = BLACK;
                x -> parent -> color = RED;
                right_rotate(tree, x -> parent);
                w = x -> parent -> left;
            }
            if(w -> right -> color == BLACK && w -> left -> color == BLACK){
                w -> color = RED;
                x = x -> parent;
            }
            else{
                if(w -> left -> color == BLACK){
                    w -> right -> color = BLACK;
                    w -> color = RED;
                    left_rotate(tree, w);
                    w = x -> parent -> left;
                }
                w -> color = x -> parent -> color;
                x -> parent -> color = BLACK;
                w -> left -> color = BLACK;
                right_rotate(tree, x -> parent);
                x = tree -> root;
            }
        }
    }
    x -> color = BLACK;
    return;
}
