#ifndef LIST_H
#define LIST_H

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

typedef struct node node;
typedef struct list list;

list *list_alloc(void (*destructor)(void *data),
                 int (*cmp)(const void *e1, const void *e2));
int list_free(list *self);

int list_insert_next(list *self, node *element, const void *data);
int list_insert_index(list *self, unsigned int index, const void* data);

void *list_remove_next(list *self, node *element);
void *list_remove_index(list *self, unsigned int index);

int list_purge_next(list *self, node* elem);
int list_purge_index(list *self, unsigned int index);

node *list_get_node_at(list *self, unsigned int index);
int is_data_in_list(list *self, void *data);
void *list_get_data(node *element);

unsigned int list_size(list *self);
#endif
