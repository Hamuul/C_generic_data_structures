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
