#include <stdlib.h>

#include "Queue.h"

void init_q(struct Queue *q) {

    q->list = malloc(sizeof(struct LinkedList));
    if (q->list == NULL) {
        perror("Not enough memory to initialize the queue!");
        return;
    }

    init_list(q->list);
}

int get_size_q(struct Queue *q) {

    if(q == NULL) return -1;
    return get_size(q->list);
}

int is_empty_q(struct Queue *q) {

    if(q->list->size == 0) return 1;
    else return 0;
}

void* front(struct Queue *q) {

    if(q == NULL || q->list == NULL) return NULL;
    return (void *) q->list->head->data;

}

void dequeue(struct Queue *q) {

    if (q == NULL) return;
    struct Node *remove;
    remove = remove_nth_node(q->list, 0);
    free(remove);
}

void enqueue(struct Queue *q, void *new_data) {
    
    if(q == NULL) return;
    add_nth_node(q->list, q->list->size, new_data);
}

void clear_q(struct Queue *q) {

    struct Node *currNode;

    if (q == NULL || q->list == NULL) {
        return;
    }

    while(get_size(q->list) > 0) {
        currNode = remove_nth_node(q->list, 0);
        free(currNode);
    }
}

void purge_q(struct Queue *q) {

    clear_q(q);
    free(q->list);
    q->list = NULL;
}