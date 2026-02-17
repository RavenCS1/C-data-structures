#include "list.h"

int main(void){
	srand(time(0));

	node* head = nullptr;
	node* new = nullptr;

    new = create(8);
	head = add_first(head, new);

	node* phead = pull_all_elements(&head, 8);
	print_list_next(phead);
    print_list_prev(phead);

    free_list(&phead);
	print_list_next(head);
	print_list_prev(head);

	int32_t table[] = {8, 1, 2, 3, 8, 8};
	for(int32_t i = 0; i < (int32_t)(sizeof(table)/sizeof(table[0])) ; ++i){
		new = create(table[i]);
		head = add_last(head, new);
	}
    new = nullptr;
	print_list_next(head);
	print_list_prev(head);

	phead = pull_all_elements(&head, 8);
	print_list_next(phead);
    print_list_prev(phead);

    free_list(&phead);
	print_list_next(head);
	print_list_prev(head);
	
    node* elem = pull_one_element(&head, 3);
    if(elem) free(elem);
	print_list_next(head);
	print_list_prev(head); 

    new = create(4);
	head = add_last(head, new);
   
    elem = pull_one_element(&head, 1);
    if(elem) free(elem);
	print_list_next(head);
	print_list_prev(head);	

    new = create(3);
	head = add_last(head, new);
    
    elem = pull_one_element(&head, 2);
    if(elem) free(elem);
    
	elem = nullptr;
	print_list_next(head);
	print_list_prev(head);

    new = create(1);
	head = add_last(head, new);

    new = create(6);
	add_sort(&head, new);	
	print_list_next(head);
	print_list_prev(head);
	
    new = create(-1);
	add_sort(&head, new);	
	print_list_next(head);
	print_list_prev(head);
    
	new = create(2);
	add_sort(&head, new);	
    
    new = create(-2);
	head = add_last(head, new);

    new = create(7);
	head = add_first(head, new);
    
    sort_divided(&head);
	print_list_next(head);
	print_list_prev(head);
    
    sort_reversed_divided(&head);
	print_list_next(head);
	print_list_prev(head);
    
    sort(&head);
	print_list_next(head);
	print_list_prev(head);

    new = nullptr;
	free_list(&head);

	return EXIT_SUCCESS;
}
