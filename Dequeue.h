#ifndef __DEQUEUE_H__
#define __DEQUEUE_H__

#include "LinkedList.h"

struct Dequeue {
    struct LinkedList *list;
};

void init_dq(struct Dequeue *dq);

int get_size_dq(struct Dequeue *dq);

int is_empty_dq(struct Dequeue *dq);

void* front(struct Dequeue *dq);

void* back(struct Dequeue *dq);

void remove_first(struct Dequeue *dq);

void remove_last(struct Dequeue *dq);

void add_first(struct Dequeue *dq, void *new_data);

void add_last(struct Dequeue *dq, void *new_data);

void clear_dq(struct Dequeue *dq);

void purge_dq(struct Dequeue *dq);

#endif /* __DEQUEUE_H__ */