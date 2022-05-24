#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef list queue;

#define queue_alloc list_alloc
#define queue_free list_free

int enqueue(queue *self, const void *data);
void *dequeue(queue *self);
int queue_purge(queue *self);
void *queue_peek(queue *self);
unsigned int queue_size(queue *self);

#endif
