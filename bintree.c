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
