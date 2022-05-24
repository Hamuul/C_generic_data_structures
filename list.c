#include <stdlib.h>
#include "list.h"

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
    if( (self = (list *) calloc(1, sizeof(*self))) != NULL)
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
        * CALLER MUST PROPERLY FREE POPPED NODE'S DATA (the returned pointer)
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

/**
        * Pops the n-th node from the list.
        * CALLER MUST PROPERLY FREE POPPED NODE'S DATA (the returned pointer)
        * INPUT:
        * 'list'		List were we operate changes.
        * 'index'		The index of the element to be removed.
        *
        * RETURNS:
        * NULL			If list is NULL, or empty.
        * 'data'		The data retrieved from the popped node.
        **/
void *list_remove_index(list *self, unsigned int index)
{
    node *tmp = NULL;
    void *data = NULL;
    if(NULL == self || index > self->size)
    {
        return NULL;
    }
    if(index == 0)
    {
        data = list_remove_next(self, NULL);
    }
    else
    {
        unsigned int i = 0;
        for(i = 0, tmp = self->head; i < index; ++i)
        {
            tmp = tmp->next;
        }
        data = list_remove_next(self, tmp);
    }
    return data;
}

/**
        *list_remove_next except it also frees popped node DATA
        *RETURNS:
        * 0 if purge (memory free by destructor call) was succesful
        * -1 if purge failed
**/
int list_purge_next(list *self, node *elem)
{
    void *data = NULL;
    if(NULL == self || NULL == self->destructor)
    {
        return -1;
    }
    data = list_remove_next(self, elem);
    if(data != NULL)
    {
        self->destructor(data);
    }
    return 0;
}

/**
        *list_remove_index except it also frees popped node DATA
        *RETURNS:
        * 0 if purge (memory free by destructor call) was succesful
        * -1 if purge failed
**/
int list_purge_index(list *self, unsigned int index)
{
    void *data = NULL;
    if(NULL == self ||  index > self->size || NULL == self->destructor)
    {
        return -1;
    }
    data = list_remove_index(self, index);
    if(data != NULL)
    {
        self->destructor(data);
    }
    return 0;
}

/**
        *INPUT :
        *'self' -> list to operate on
        *'index' -> position from which to get node
        *RETURNS:
        * NULL if there is node node at the given index
        * Pointer to the node at the given index otherwise
**/
node *list_get_node_at(list *self, unsigned int index)
{
    node *tmp = NULL;
    if(NULL == self || index > self->size)
    {
        return NULL;
    }
    unsigned int i;
    for(i = 0, tmp = self->head; i < index; i++)
    {
        tmp = tmp->next;
    }
    return tmp;
}

int is_data_in_list(list *self, void *data)
{
    node *tmp = NULL;
    unsigned int i;
    for(i = 0, tmp = self->head; i < self->size; i++)
    {
        if(self->cmp(tmp->data, data) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void *list_get_data(node *element)
{
	return (element == NULL) ? NULL : element->data;
}

unsigned int list_size(list *self)
{
	return (self == NULL) ? 0 : self->size;
}
