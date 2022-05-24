#ifndef LIST_H
#define LIST_H

typedef struct node node;
typedef struct list list;

list *list_alloc(void (*destructor)(void *data));
int list_free(list *self);

int list_insert_next(list *list, node *element, const void *data);


void *list_remove_next(list *self, node *element);

#endif
