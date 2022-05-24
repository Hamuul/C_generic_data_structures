#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct node {
	void *data;
	struct node *next;
};


struct list {
	void (*destructor)(void *data);
	int (*cmp)(const void *e1, const void *e2);
	unsigned int size;
	struct node *head;
	struct node *tail;
};


list *list_alloc(void (*destructor) (void *data))
{
    list *self = NULL;
    if( (self = (list *) calloc(1, sizeof(list *))) != NULL)
    {
        self->size = 0;
        self->destructor = destructor;
        self->head = NULL;
        self->tail = NULL;
    }

}
