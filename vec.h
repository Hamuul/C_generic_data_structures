#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <string.h>

#define vec_unpack_(v)\
    (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)

#define vec_t(T)\
    struct {T* data; int length, capacity;}

#define vec_init(v)\
    memset((v), 0, sizeof(*(v)))

#define vec_deinit(v)\
    ( free((v))->data,\
      vec_init(v) )

#define vec_push(v, val)\
    ( vec_expand_(vec_unpack_(v)) ? -1 :\
      ((v)->data[(v)->length++] = (val), 0), 0)

#define vec_pop(v)\
    (v)->data[--(v)->length];

#define vec_splice(v, start, count)\
    ( vec_splice_(vec_unpack_(v), start, count)),\
      (v)->length -= count )

#define vec_insert(v, idx, val)\
    ( vec_insert_(vec_unpack_(v), idx)) ? -1 :\
      ((v)->data[idx] = (val), 0), (v)->length++, 0)

#define vec_sort(v, cmp)\
    qsort((v)->data, (v)->length, sizeof(*(v)->data), cmp)

#define vec_swap(v, idx1, idx2)\
    vec_swap_(vec_unpack_(v), idx1, idx2)

int vec_expand_(char **data, int *length, int *capacity, int memsz);
int vec_insert_(char **data, int *length, int *capacity, int memsz, int idx);
void vec_splice_(char **data, int *length, int *capacity, int memsz,
                 int start, int count);

typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(float) vec_float_t;
typedef vec_t(double) vec_double_t;
#endif
