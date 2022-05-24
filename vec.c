#include "vec.h"

int vec_expand_(char ** data, int *length, int *capacity, int memsz)
{
   if (*length + 1 > *capacity)
   {
   void *ptr;
   int n = (*capacity == 0) ? 1 : *capacity << 1;
   ptr = realloc(*data, n * memsz);
   if (ptr == NULL)
   {
       return -1;
   }
   *data = (char*) ptr;
   *capacity = n;
    }
    return 0;
}
