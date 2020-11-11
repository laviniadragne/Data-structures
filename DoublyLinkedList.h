#ifndef __DOUBLYLINKEDLIST_H__
#define __DOUBLYLINKEDLIST_H__

struct Node {
    // char tag[4];
    // char title[31];
    // char artist[31];
    // char album[31];
    // char an[5];
    void *data;
    struct Node *next, *prev;
};

struct DoublyLinkedList {
	struct Node *head, *tail;
	//struct Node *cur;
	int size;
    
};

void init_list(struct DoublyLinkedList *list);

/*
 * Acestea sunt functiile pe care trebuie sa le implementam.
 * Implementarea acestora se va face in LinkedList.c .
 */

struct Node* get_nth_node(struct DoublyLinkedList *list, int n);

void add_nth_node(struct DoublyLinkedList *list, int n, void *new_data);

struct Node* remove_nth_node(struct DoublyLinkedList *list, int n);

int get_size(struct DoublyLinkedList *list);

void free_list(struct DoublyLinkedList **pp_list);

void print_int_list(struct DoublyLinkedList *list);

void print_string_list(struct DoublyLinkedList *list);

// void print_ints_left_circular(struct Node *start);

// void print_ints_right_circular(struct Node *start);

#endif /* __DOUBLYLINKEDLIST_H__ */