#ifndef BINTREE_H
#define BINTREE_H

struct bintree_node{
	void *data;
	struct nmbintree_node_s *right;
	struct nmbintree_node_s *left;
};

struct bintree{
	unsigned int size;
	int (*cmp)(const void *e1, const void *e2);
	void (*destructor)(void *data);
	bintree_node *root;
};

typedef bintree_node node;

bintree *bintree_alloc(void (*destructor)(void *data),
                     int (*cmp) (const void* e1, const void *e2));
#endif
