#include "brtree.h"

int main(void){
    holder* tree = allocate_holder();
    leaf* tmp = nullptr;
    int32_t i_val_1[] = {10, 5, 1, 15, 20, 18, 25, 30, 2, 8, 6, 12, 14, 7, 3, 4};
    
    for(int32_t i = 0; i < NUMBER_OF_ELEM(i_val_1); ++i){
        tmp = allocate_leaf(i_val_1[i]);
        if(tree -> root) rb_insert(tree, tmp);
        else{
            tree -> root = tmp;
            tree -> root -> color = BLACK;
            tree -> root -> parent = tree -> guard;
            tree -> root -> left = tree -> root -> right = tree -> guard;
            tree -> number_of_elem += 1;
        }
    }

    (void) printf("Inorder_tree_walk:\n\n");
    inorder_tree_walk(tree, tree -> root);

    (void) printf("Preorder_tree_walk:\n\n");
    preorder_tree_walk(tree, tree -> root);

    (void) printf("Postorder_tree_walk:\n\n");
    postorder_tree_walk(tree, tree -> root);
    
    leaf* result1 = tree_search(tree, tree -> root, 30);
    leaf* result2 = iterative_tree_search(tree, tree -> root, 11);

    if(result1 != tree -> guard){(void) printf("Search for the leaf with key of value 30 found:\n\n"); print_leaf(tree, result1);}
    if(result2 != tree -> guard){(void) printf("Search for the leaf with key of value 11 found:\n\n"); print_leaf(tree, result2);}

    leaf* min = tree_minimum(tree, tree -> root);
    leaf* max = tree_maximum(tree, tree -> root);

    if(min != tree -> guard){(void) printf("Minimal value in the Red-black tree:\n\n"); print_leaf(tree, min);}
    if(max != tree -> guard){(void) printf("Maximal value in the Red-black tree:\n\n"); print_leaf(tree, max);}
    
    leaf* successor = tree_successor(tree, min);
    leaf* predecessor = tree_predecessor(tree, max);

    if(successor != tree -> guard){(void) printf("Successor of the node with minimal value in the Red-black tree:\n\n"); print_leaf(tree, successor);}
    if(predecessor != tree -> guard){(void) printf("Predecessor of the node with maximal value in the Red-black tree:\n\n"); print_leaf(tree, predecessor);}

    int32_t d_val_1[] = {4, 7, 14, 18, 25, 30};
    int32_t d_val_2[] = {6, 8, 12};
    int32_t d_val_3[] = {5, 10, 15};
    
    leaf* delete = nullptr;

    for(int32_t i = 0; i < NUMBER_OF_ELEM(d_val_1); ++i){
        delete = iterative_tree_search(tree, tree -> root, d_val_1[i]);
        rb_delete(tree, delete);
    }

    (void) printf("Inorder_tree_walk:\n\n");
    inorder_tree_walk(tree, tree -> root);

    for(int32_t i = 0; i < NUMBER_OF_ELEM(d_val_2); ++i){
        delete = iterative_tree_search(tree, tree -> root, d_val_2[i]);
        rb_delete(tree, delete);
    }

    (void) printf("Inorder_tree_walk:\n\n");
    inorder_tree_walk(tree, tree -> root);
    
    for(int32_t i = 0; i < NUMBER_OF_ELEM(d_val_3); ++i){
        delete = iterative_tree_search(tree, tree -> root, d_val_3[i]);
        rb_delete(tree, delete);
    }
    (void) printf("Inorder_tree_walk:\n\n");
    inorder_tree_walk(tree, tree -> root);
    
    free_tree(tree, tree -> root);
    free_holder(&tree);
    
    return EXIT_SUCCESS;
}
