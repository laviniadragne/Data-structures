#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

void init_stack(struct Stack *stack) {

    stack->list = malloc(sizeof(struct LinkedList));
    if (stack->list == NULL) {
        perror("Not enough memory to initialize the stack!");
        return;
    }

    init_list(stack->list);
}

int get_size_stack(struct Stack *stack) {

    if(stack == NULL) return -1;
    else {
        return get_size(stack->list);
    }
}

int is_empty_stack(struct Stack *stack) {
    
    if(stack->list->size == 0) return 1;
    else return 0;
}

void* peek_stack(struct Stack *stack) {

    if(stack == NULL || stack->list == NULL || stack->list->size == 0) return NULL;
    return (void *) stack->list->head->data;

    
}

void pop_stack(struct Stack *stack) {

    if (stack == NULL) return;
    struct Node *remove;
    remove = remove_nth_node(stack->list, 0);
    free(remove->data);
    free(remove);
}

void push_stack(struct Stack *stack, void *new_data) {
    
    if(stack == NULL) return;
    add_nth_node(stack->list, 0, new_data);
}

void clear_stack(struct Stack *stack) {
    
    struct Node *currNode;

    if (stack == NULL || stack->list == NULL) {
        return;
    }

    while(get_size(stack->list) > 0) {
        currNode = remove_nth_node(stack->list, 0);
        free(currNode->data);
        free(currNode);
    }
}

void purge_stack(struct Stack *stack) {

    clear_stack(stack);
    free(stack->list);
    stack->list = NULL;
}
