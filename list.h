#ifndef LIST_H
#define LIST_H

typedef struct node node;
typedef struct list list;

list *list_alloc(void (*destructor)(void *data));
int list_free(list *self);


void *list_remove_next(list *self, node *element);

#endif
