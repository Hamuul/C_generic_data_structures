#include <stdlib.h>
#include "queue.h"

int enqueue(queue *self, const void *data)
{
    return (self == NULL)? (NULL) : list_insert_next(self, self->tail, data);
}

void *dequeue(queue *self)
{
    return list_remove_next(self, NULL);
}

int queue_purge(queue *self)
{
    return list_purge_next(self, NULL);
}

void *queue_peek(queue *self)
{
    return list_get_data(self->head);
}

unsigned int queue_size(queue *self)
{
    return list_size(self);
}
