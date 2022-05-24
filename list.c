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

/**
        * Reserve memory for new linked list.
        * INPUT :
        * 'destructor' -> user defined destructor for void* data
        * OUTPUT:
        * pointer to the new linked list wrapper struct or NULL (alloc error)
**/
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
    return self;
}

/**
        * Deallocates memory used by linked list.
        * INPUT :
        * 'self' -> pointer to the list wrapper for the list to be dealloced
        * OUTPUT:
        * 0 if there is nothing to free, 1 if freeing was succesful
**/
int list_free(list *self)
{
    void *tmp;
    if(NULL == self || NULL == self->destructor)
    {
        return 0;
    }
    while(self->size > 0)
    {
        if( (tmp = list_remove_next(self, NULL)) != NULL)
        {
            self->destructor(tmp);
        }
    }
    free(self);
    return 1;
}
