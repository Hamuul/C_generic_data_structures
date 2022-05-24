#include "vec.h"

int vec_expand_(char **data, int *length, int *capacity, int memsz)
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

void vec_splice_(char **data, int *length, int *capacity, int memsz,
                 int start, int count)
{
    (void) capacity;
    memmove(*data + start * memsz, *data + (start + count) * memsz,
            (*length - start - count) * memsz);
}
