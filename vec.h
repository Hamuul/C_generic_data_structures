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

#define vec_push(v, val)

int vec_expand_(char **data, int *length, int *capacity, int memsz);

typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(float) vec_float_t;
typedef vec_t(double) vec_double_t;
#endif
