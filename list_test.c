#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct person{
    char *name;
    unsigned height;
    unsigned weight;
    struct children{
        char *first;
        char *second;
    }children;
    char *SSN;
}person;

void destructor(void *self)
{
    struct person *tmp = (struct person *) self;
    free(tmp->name);
    free(tmp->SSN);
    free(tmp->children.first);
    free(tmp->children.second);
}

char *my_strdup(char *src)
{
    char *dest = (char *) calloc(strlen(src) + 1, sizeof(char));
    if(!dest)
    {
        strcpy(dest, src);
    }
    return dest;
}

int main(void)
{
    list my_list;
    list* lptr = &my_list;
    lptr = list_alloc(destructor);
    person dorel;
    dorel.name = my_strdup("dorel");
    dorel.SSN = my_strdup("32543544364365");
    dorel.children.first = my_strdup("juniora");
    dorel.children.second = my_strdup("junior");
    person dorela;
    dorela.name = my_strdup("dorela");
    dorela.SSN = my_strdup("876888768588585");
    dorela.children.first = my_strdup("juniora");
    dorela.children.second = my_strdup("junior");
    list_insert_index(lptr, 0, (void *) &dorel);
    list_insert_index(lptr, 1, (void *) &dorela);
    list_free(lptr);
    return 0;
}
