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

int vec_insert_(char **data, int *length, int *capacity, int memsz, int idx)
{
  int err = vec_expand_(data, length, capacity, memsz);
  if (err) return err;
  memmove(*data + (idx + 1) * memsz,
          *data + idx * memsz,
          (*length - idx) * memsz);
  return 0;
}

void vec_splice_(char **data, int *length, int *capacity, int memsz,
                 int start, int count)
{
    (void) capacity;
    memmove(*data + start * memsz, *data + (start + count) * memsz,
            (*length - start - count) * memsz);
}

void vec_swap_(char **data, int *length, int *capacity, int memsz,
               int idx1, int idx2)
{
    unsigned char *a, *b, tmp;
    int count;
    (void) length;
    (void) capacity;
    if(idx1 == idx2)
    {
        return;
    }
    a = (unsigned char *) *data + idx1 * memsz;
    b = (unsigned char *) *data + idx2 * memsz;
    count = memsz;
    while(count--)
    {
        tmp = *a;
        *a = *b;
        *b = tmp;
        ++a;
        ++b;
    }
}
