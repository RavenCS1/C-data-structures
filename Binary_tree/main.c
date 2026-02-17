#include "tree.h"

int main(void){
    srand(time(0));

    node* root = nullptr;
    node* new = nullptr;

    for(int32_t i = 0; i < N; ++i){
        new = create(rand_int32_t(1, 20));
        tree_insert(&root, new);
    }

    (void) printf("Inorder_tree_walk:\n\n");
    inorder_tree_walk(root);

    (void) printf("Preorder_tree_walk:\n\n");
    preorder_tree_walk(root);

    (void) printf("Postorder_tree_walk:\n\n");
    postorder_tree_walk(root);

    node* found1 = tree_search(root, rand_int32_t(1, 20));
    if(found1){
        (void) printf("Tree_search found:\n");
        print_leaf(found1);
    }

    node* found2 = iterative_tree_search(root, rand_int32_t(1, 20));
    if(found2){
        (void) printf("Iterative_tree_search found:\n");
        print_leaf(found2);
    }

    node* min = tree_minimum(root);
    (void) printf("Minimal value of the tree:\n");
    print_leaf(min);

    node* max = tree_maximum(root);
    (void) printf("Maximal value of the tree:\n");
    print_leaf(max);

    node* suc = tree_successor(min);
    (void) printf("Successor of the node with minimal value of the tree:\n");
    print_leaf(suc);

    node* pre = tree_predecessor(max);
    (void) printf("Predecessor of the node with maximal value of the tree:\n");
    print_leaf(pre);

    for(int32_t i = 0; i < N / 2; ++i){
        node* todelete = iterative_tree_search(root, rand_int32_t(1,20));
        if(todelete){
            (void) printf("Dealocation of a node:\n");
            print_leaf(todelete);
            tree_delete(&root, todelete);
        }
    }
    (void) printf("Inorder_tree_walk:\n\n");
    inorder_tree_walk(root);

    free_tree(&root);
    
    return EXIT_SUCCESS;
}
