#include "list.h"

node* create(int32_t key){
	node* new = malloc(sizeof(*new));
	if(!new){
		(void) printf("Allocation of a new node was unfortunately unsuccesful!\n");
		exit(EXIT_FAILURE);
	}
	new -> value = key;
	new -> next = new -> prev = nullptr;
	return new;
}

void print_node(node* x){
    if(x){
        (void) printf("Adress of the node: %p\n", (void *)x);
        (void) printf("Value of the key: %" PRId32 "\n", x -> value);
        (void) printf("Adress of the previous node: %p\n", (void *)(x -> prev));
        (void) printf("Adress of the next node: %p\n\n", (void *)(x -> next));
    }
    else (void) printf("Invalid pointer! Couldn't print out pieces of information about a node.\n");
    return;
}

void print_list_next(node* head){
	if(!head){
		(void) printf("List is currently empty!\n\n");
		return;
	}
	(void) printf("Printing the list in normal order.\n\n");
	for(node* iterator = head; iterator; iterator = iterator -> next)
		print_node(iterator);
	return;
}

void print_list_prev(node* head){
	if(!head){
		printf("List is currently empty!\n\n");
		return;
	}
	(void) printf("Printing the list in the reversed order.\n\n");
    node* iterator = head;
	for(; iterator -> next; iterator = iterator -> next);
    for(; iterator; iterator = iterator -> prev)
		print_node(iterator);
	return;
}

node* add_first(node* head, node* elem){
	if(!head) return elem;
	elem -> next = head;
	head -> prev = elem;
	(void) printf("A new node was added at the beginning of the list!\n\n");
	print_node(elem);
	return elem;
}

node* add_last(node* head, node* elem){
	if(!head) return elem;
	node* iterator = head;
    for(; iterator -> next; iterator = iterator -> next);
    iterator -> next = elem;
	elem -> prev = iterator;
	(void) printf("A new node was added at the end of the list!\n\n");
	print_node(elem);
	return head;
}

node* pull_all_elements(node** head, int32_t key){
	if(!(*head)){
		(void) printf("List is currently empty!\n\n");
		return nullptr;
	}
	node* new_head = nullptr;
	node* prev = (*head) -> prev;
	node* next = (*head) -> next;
	node* iterator = *head;
	while(iterator){
		if(iterator -> value == key){
			iterator -> next = iterator -> prev = nullptr;
			new_head = add_first(new_head, iterator);
			if(!prev){
				if(next){
					next -> prev = prev;
                    *head = next;
                }
				else{
			        *head = nullptr;
                    return new_head;  
                }
			}
			else{
				if(next){
					prev -> next = next;
					next -> prev = prev;
				}
				else prev -> next = next;
			}
		}
		iterator = next;
		if(iterator){
			prev = iterator -> prev;
			next = iterator -> next;
		}
	}
	(void) printf("All nodes with the key value of: %" PRId32 " were extracted from the original list\n\n", key);
	return new_head;
}

node* pull_one_element(node** head, int32_t key){
	if(!(*head)){
		(void) printf("List is currently empty!\n\n");
		return nullptr;
	}
	node* prev = (*head) -> prev;
	node* next = (*head) -> next;
	node* iterator = *head;
	while(iterator && (iterator -> value != key)){
		iterator = next;
		if(iterator){
			prev = iterator -> prev;
			next = iterator -> next;
		}
	}
	if(iterator){
        if(iterator == *head) *head = next;
		if(prev) prev -> next = next;
		if(next) next -> prev = prev;
        iterator -> next = iterator -> prev = nullptr;
		(void) printf("A node was extracted from the list\n\n");
		print_node(iterator);
		return iterator;
	}
	return nullptr;
}

void add_sort(node** head, node* elem){
	if(!(*head)){
		*head = elem;
		return;
	}
	node* iterator = *head;
	if(elem -> value <= iterator -> value){
		*head = elem;
		elem -> next = iterator;
		iterator -> prev = elem;
		return;
	}
	node* prev = iterator;
	iterator = iterator -> next;
	while(iterator){
		if(elem -> value <= iterator -> value){
			prev -> next = elem;
			elem -> prev = prev;
			elem -> next = iterator;
			iterator -> prev = elem;
			return;		
		}
		prev = iterator;
		iterator = iterator -> next;
	}
	prev -> next = elem;
	elem -> prev = prev;
	(void) printf("A new node was added in the sorted order!\n\n");
	print_node(elem);
	return;			
}

void sort_divided(node** head){
    if(!((*head) -> next)) return;
    bool check = false;
	node* tmp_head = *head;
	node* tmp_insert, *prev_insert, *prev, *next;
	for(node* iterator = tmp_head -> next; iterator; iterator = next){
		prev = iterator -> prev;
		next = iterator -> next;
		tmp_insert = tmp_head;
		prev_insert = tmp_head -> prev;
		if(iterator -> value % 2 == 0){
			while((tmp_insert) && (tmp_insert -> value % 2 == 0) && 
                  (tmp_insert -> value <= iterator -> value)){
				prev_insert = tmp_insert;
				tmp_insert = tmp_insert -> next;
			}
            if(prev_insert != iterator){
			    prev -> next = next;
			    if(next) next -> prev = prev;
			    if(!prev_insert){
				    tmp_head = iterator;
				    iterator -> prev = nullptr;
				    iterator -> next = tmp_insert;
                    tmp_insert -> prev = iterator;
                    check = true;
			    }
			    else{
				    prev_insert -> next = iterator;
				    iterator -> prev = prev_insert;
				    if(tmp_insert) tmp_insert -> prev = iterator;
				    iterator -> next = tmp_insert;
			    }
            }
		}
		else{
            if(check == false){
			    while(tmp_insert && (tmp_insert -> value <= iterator -> value) &&
                      ((tmp_insert -> value % 2 == 1) || (tmp_insert -> value % 2 == -1))){
				    prev_insert = tmp_insert;
				    tmp_insert = tmp_insert -> next;
			    }
            }
            else{
			    while((tmp_insert) && 
                      ((tmp_insert -> value % 2 == 0) || (tmp_insert -> value <= iterator -> value))){
				    prev_insert = tmp_insert;
				    tmp_insert = tmp_insert -> next;
			    }
            }
            if(prev_insert != iterator){
			    prev -> next = next;
			    if(next) next -> prev = prev;
			    if(!prev_insert){
				    tmp_head = iterator;
				    iterator -> prev = nullptr;
				    iterator -> next = tmp_insert;
                    tmp_insert -> prev = iterator;
			    }
			    else{
				    prev_insert -> next = iterator;
				    iterator -> prev = prev_insert;
				    if(tmp_insert)
                        tmp_insert -> prev = iterator;
				    iterator -> next = tmp_insert;
			    }
            }
		}
	}
    *head = tmp_head;
	(void) printf("List was sorted in the divided order (first even numbers, then odd)!\n\n");
	return;
}

void sort_reversed_divided(node** head){
    if(!((*head) -> next)) return;
    bool check = false;
	node* tmp_head = *head;
	node* tmp_insert, *prev_insert, *prev, *next;
	for(node* iterator = tmp_head -> next; iterator; iterator = next){
		prev = iterator -> prev;
		next = iterator -> next;
		tmp_insert = tmp_head;
		prev_insert = tmp_head -> prev;
		if((iterator -> value % 2 == 1) || (iterator -> value % 2 == -1)){
			while((tmp_insert) && (tmp_insert -> value <= iterator -> value) &&
                  ((tmp_insert -> value % 2 == 1) || (tmp_insert -> value % 2 == -1))){
				prev_insert = tmp_insert;
				tmp_insert = tmp_insert -> next;
			}
            if(prev_insert != iterator){
			    prev -> next = next;
			    if(next) next -> prev = prev;
			    if(!prev_insert){
				    tmp_head = iterator;
				    iterator -> prev = nullptr;
				    iterator -> next = tmp_insert;
                    tmp_insert -> prev = iterator;
                    check = true;
			    }
			    else{
				    prev_insert -> next = iterator;
				    iterator -> prev = prev_insert;
				    if(tmp_insert) tmp_insert -> prev = iterator;
				    iterator -> next = tmp_insert;
			    }
            }
		}
		else{
            if(!check){
			    while((tmp_insert) && (tmp_insert -> value % 2 == 0) && 
                      (tmp_insert -> value <= iterator -> value)){
				    prev_insert = tmp_insert;
				    tmp_insert = tmp_insert -> next;
			    }
            }
            else{
			    while((tmp_insert) && ((tmp_insert -> value % 2 == 1) ||  
                      (tmp_insert -> value % 2 == -1) || (tmp_insert -> value <= iterator -> value))){
				    prev_insert = tmp_insert;
				    tmp_insert = tmp_insert -> next;
			    }
            }
            if(prev_insert != iterator){
			    prev -> next = next;
			    if(next) next -> prev = prev;
			    if(!prev_insert){
				    tmp_head = iterator;
				    iterator -> prev = nullptr;
				    iterator -> next = tmp_insert;
                    tmp_insert -> prev = iterator;
			    }
			    else{
				    prev_insert -> next = iterator;
				    iterator -> prev = prev_insert;
				    if(tmp_insert) tmp_insert -> prev = iterator;
				    iterator -> next = tmp_insert;
			    }
            }
		}
	}
    *head = tmp_head;
	(void) printf("List was sorted in the reversed divided order (first odd numbers, then even)!\n\n");
	return;
}

void sort(node** head){
    if(!((*head) -> next)) return;
	node* tmp_head = *head;
	node* tmp_insert, *prev_insert, *prev, *next;
	for(node* iterator = tmp_head -> next; iterator; iterator = next){
		prev = iterator -> prev;
		next = iterator -> next;
		tmp_insert = tmp_head;
		prev_insert = tmp_head -> prev;
	    while(tmp_insert && (tmp_insert -> value <= iterator -> value)){
		    prev_insert = tmp_insert;
			tmp_insert = tmp_insert -> next;
		}
        if(prev_insert != iterator){
		    prev -> next = next;
		    if(next) next -> prev = prev;
		    if(!prev_insert){
			    tmp_head = iterator;
			    iterator -> prev = nullptr;
			    iterator -> next = tmp_insert;
                tmp_insert -> prev = iterator;
		    }
		    else{
			    prev_insert -> next = iterator;
			    iterator -> prev = prev_insert;
			    if(tmp_insert) tmp_insert -> prev = iterator;
			    iterator -> next = tmp_insert;
		    }
        }
	}
    *head = tmp_head;
	(void) printf("List was sorted in a normal order!\n\n");
	return;
}

void free_list(node** head){
	node* handle = nullptr;
	while(*head){
		handle = *head;
		*head = (*head) -> next;
		(void) printf("Deallocation of a node:\n\n");
		print_node(handle);
		memset(handle, 0, sizeof(*handle));
		free(handle);
	}
	handle = nullptr;
	return;
}


