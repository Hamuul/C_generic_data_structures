#ifndef BINTREE_H
#define BINTREE_H

struct bintree_node{
	void *data;
	struct bintree_node *right;
	struct bintree_node *left;
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
int bintree_purge_right(bintree *tree, node *treenode);
int bintree_purge_left(bintree *tree, node *treenode);

int bintree_free(bintree *tree);

int bintree_add_left(bintree *tree, node *treenode, const void *data);
int bintree_add_right(bintree *tree, node *treenode, const void *data);

bintree *bintree_merge(bintree *leftree, bintree *rightree,
                           void (*destructor)(void *val),
                           int (*cmp)(const void *e1, const void *e2),
                           const void *data);

#endif
