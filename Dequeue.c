#include <stdlib.h>

#include "Dequeue.h"


void init_dq(struct Dequeue *dq) {

    dq->list = malloc(sizeof(struct LinkedList));
    if (dq->list == NULL) {
        perror("Not enough memory to initialize the dequeue!");
        return;
    }

    init_list(dq->list);
}

int get_size_dq(struct Dequeue *dq) {

    if(dq == NULL) return -1;
    return get_size(dq->list);
}

int is_empty_dq(struct Dequeue *dq) {

    if(dq->list->size == 0) return 1;
    else return 0;
}

void* front(struct Dequeue *dq) {

    if(dq == NULL || dq->list == NULL) return NULL;
    return (void *) dq->list->head->data;

}

void* back(struct Dequeue *dq) {

    if(dq == NULL || dq->list == NULL) return NULL;
    return (void *) dq->list->tail->data;

}

void remove_first(struct Dequeue *dq) {

    if (dq == NULL) return;
    struct Node *remove;
    remove = remove_nth_node(dq->list, 0);
    free(remove);
}

void remove_last(struct Dequeue *dq) {

    if (dq == NULL) return;
    struct Node *remove;
    remove = remove_nth_node(dq->list, dq->list->size - 1);
    free(remove);
}

void add_first(struct Dequeue *dq, void *new_data) {
    
    if(dq == NULL) return;
    add_nth_node(dq->list, 0 , new_data);
}

void add_last(struct Dequeue *dq, void *new_data) {
    
    if(dq == NULL) return;
    add_nth_node(dq->list, dq->list->size, new_data);
}

void clear_dq(struct Dequeue *dq) {

    struct Node *currNode;

    if (dq == NULL || dq->list == NULL) {
        return;
    }

    while(get_size(dq->list) > 0) {
        currNode = remove_nth_node(dq->list, 0);
        free(currNode);
    }
}

void purge_dq(struct Dequeue *dq) {
    
    clear_dq(dq);
    free(dq->list);
    dq->list = NULL;
}