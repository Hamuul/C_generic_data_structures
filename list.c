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
        * -1 if there is nothing to free, 0 if freeing was succesful
**/
int list_free(list *self)
{
    void *tmp;
    if(NULL == self || NULL == self->destructor)
    {
        return -1;
    }
    while(self->size > 0)
    {
        if( (tmp = list_remove_next(self, NULL)) != NULL)
        {
            self->destructor(tmp);
        }
    }
    free(self);
    return 0;
}

/**
        *Inserts a new node into a previously alloced list.
        *If 'elem' is NULL, new_elem is inserted at head.
        *INPUT:
        *'self' -> pointer to list wrapper of the list in which we insert
        *'elem' -> node after which insertion is made
        *'data' -> data to which new node will point

**/
int list_insert_next(list *self, node *elem, const void *data)
{
    node *new_elem = NULL;
    new_elem = (node *)calloc(1, sizeof(*new_elem));
    if(self == NULL || new_elem == NULL)
    {
        return -1;
    }
    new_elem->data = (void *) data;
    new_elem->next = NULL;
    if(NULL == elem)
    {
        if(self->size == 0)
        {
             self->tail = new_elem;
        }
        new_elem->next = self->head;
        self->head = new_elem;
    }
    else
    {
        if(elem->next == NULL)
        {
            self->tail = new_elem;
        }
        new_elem->next =  elem->next;
        elem->next = new_elem;
    }
    self->size += 1;
    return 0;
}

/**
        * Inserts a new element into the list at the specified index.
        *
        * INPUT:3
        * 'list'		List were we operate changes.
        * 'index'		Were to insert new element.
        * 'data'		Data to be inserted into the list
        *
        * RETURNS:
        * 0			If insertion was succesful.
        * -1			If the insertion wasn't succesful.
        * 				('list' is NULL, memory allocation failed for new
        * 				element).
 **/
int list_insert_index(list *self, unsigned int index, const void* data)
{
    node* tmp = NULL;
    if(NULL == self || index > self->size)
    {
        return -1;
    }
    if(index == 0)
    {
        list_insert_next(self, NULL, data);
    }
    else
    {
        unsigned i;
        for(i = 0, tmp = self->head; i < index; ++i)
        {
            tmp = tmp->next;
        }
        list_insert_next(self, tmp, data);
    }
    return 0;
}

/**
        * Pops the node after the specified node.
        *
        * If element is NULL the current head is removed.
        *
        * INPUT:
        * 'list'		List were we operate changes.
        * 'element'	The node at 'element->next' will be removed, and
        * its data will be returned.
        * RETURNS:
        * NULL			If list is NULL, or empty.
        * 'data'		The data retrieved from the popped node.
 **/
void *list_remove_next(list *self, node* elem)
{
    void *data = NULL;
    node *old_elem = NULL;
    if(NULL == self ||  self->size == 0)
    {
        return NULL;
    }
    if(elem == NULL)
    {
        data = self->head->data;
        old_elem = self->head;
        self->head = self->head->next;
        if(self->size == 1)
        {
            self->tail = NULL;
        }
    }
    else
    {
        if(elem->next == NULL)
        {
            return NULL;
        }
        data = elem->next->data;
        old_elem = elem->next;
        elem->next = old_elem->next;
        if(elem->next == NULL)
        {
            self->tail = elem;
        }
    }
    free(old_elem);
    self->size -= 1;
    return data;
}
