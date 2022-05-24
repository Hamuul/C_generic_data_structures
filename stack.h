#ifndef STACK_H
#define STACK_H

#include "list.h"

#define stack_alloc list_alloc
#define stack_free list_free

typedef list stack;

int stack_push(stack* self, const void* data);
void* stack_pop(stack* self);
int stack_purge(stack *self);
void *stack_peek(stack *self);
unsigned int stack_size(stack *self);

#endif
