#include <stdlib.h>
#include "stack.h"

int stack_push(stack *self, const void *data)
{
    return list_insert_next(self, NULL, data);
}

void* stack_pop(stack *self)
{
    return list_remove_next(self, NULL);
}

int stack_purge(stack *self)
{
    return list_purge_next(self, NULL);
}

void *stack_peek(stack *self)
{
    return (self == NULL)? (NULL) : list_get_data(self->head);
}

unsigned int stack_size(stack *self)
{
    return list_size(self);
}
