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
