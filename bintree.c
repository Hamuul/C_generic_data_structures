#include <stdlib.h>
#include "bintree.h"

bintree *bintree_alloc(void (*destructor)(void *data),
                     int (*cmp) (const void* e1, const void *e2))
{
    bintree *tree = NULL;
    if((tree = (bintree*) malloc(sizeof(*tree))) != NULL)
    {
        tree->size = 0;
        tree->root = NULL;
        tree->destructor = destructor;
        tree->cmp = cmp;
    }
    return tree;
}

/* This function is private */
static unsigned int bintree_purge(node *treenode, void (*destructor)(void *data))
{
    node *left, *right;
    if(treenode == NULL || destructor == NULL)
    {
        return 0;
    }
    left = treenode->left;
    right = treenode->right;
    destructor(treenode->data);
    free(treenode);
    return (bintree_purge(left, destructor)
            + bintree_purge(right, destructor) + 1);
}

int bintree_purge_left(bintree *tree, node *treenode)
{
    node **start_node = NULL;
    if(tree == NULL || tree->destructor == NULL)
    {
        return -1;
    }
    if(treenode == NULL)
    {
        if(tree == NULL)
        {
            return -1;
        }
        start_node = &tree->root;
    }
    else
    {
        start_node = &treenode->left;
    }
    tree->size -= bintree_purge(*start_node, tree->destructor);
    return 0;
}

int bintree_purge_right(bintree *tree, node *treenode)
{
    node **start_node = NULL;
    if(tree == NULL || tree->destructor == NULL)
    {
        return -1;
    }
    if(treenode == NULL)
    {
        if(tree == NULL)
        {
            return -1;
        }
        start_node = &tree->root;
    }
    else
    {
        start_node = &treenode->right;
    }
    tree->size -= bintree_purge(*start_node, tree->destructor);
    return 0;
}

int bintree_free(bintree *tree)
{
    if(tree == NULL || tree->destructor == NULL)
    {
        return -1;
    }
    if(tree->size != 0)
    {
        bintree_purge_left(tree, NULL);
    }
    free(tree);
    return 0;
}

int bintree_add_left(bintree *tree, node *treenode, const void *data)
{
    node *new_node = NULL;
    node **where_to = NULL;
    if(tree == NULL)
    {
        return -1;
    }
    if(treenode == NULL)
    {
        if(tree->size == 0)
        {
            return -1;
        }
        where_to = &tree->root;
    }
    else
    {
        if(treenode->right != NULL)
        {
            return -1;
        }
        where_to = &treenode->left;
    }
    new_node = (node *)malloc(sizeof(*new_node));
    if(new_node == NULL)
    {
        return -1;
    }
    new_node->data = (void*) data;
    new_node->left = NULL;
    new_node->right = NULL;
    tree->size++;
    return 0;
}

int bintree_add_right(bintree *tree, node *treenode, const void *data)
{
    node *new_node = NULL;
    node **where_to = NULL;
    if(tree == NULL)
    {
        return -1;
    }
    if(treenode == NULL)
    {
        if(tree->size == 0)
        {
            return -1;
        }
        where_to = &tree->root;
    }
    else
    {
        if(treenode->right != NULL)
        {
            return -1;
        }
        where_to = &treenode->right;
    }
    new_node = (node *)malloc(sizeof(*new_node));
    if(new_node == NULL)
    {
        return -1;
    }
    new_node->data = (void*) data;
    new_node->left = NULL;
    new_node->right = NULL;
    tree->size++;
    return 0;
}

bintree *bintree_merge(bintree *leftree, bintree *rightree,
                           void (*destructor)(void *val),
                           int (*cmp)(const void *e1, const void *e2),
                           const void *data)
{
    bintree *tree = NULL;
    if(leftree == NULL || rightree == NULL)
    {
        return NULL;
    }
    tree = bintree_alloc(destructor, cmp);
    if(tree == NULL)
    {
        return NULL;
    }
    if (bintree_add_left(tree, NULL, data) == -1)
    {
		free(tree);
		return NULL;
	}
    tree->size += (leftree->size + rightree->size);
	tree->root->left = leftree->root;
	tree->root->right = rightree->root;
	return tree;
}
