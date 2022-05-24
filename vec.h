#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <string.h>

#define vec_unpack_(v)\
    (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)

#define vec_t(T)\
    struct {T* data; int length, capacity}

#define vec_init(v)\
    memset((v), 0, sizeof(*(v)))

#define vec_deinit(v)\
    ( free((v))->data,\
      vec_init(v) )

#define vec_push(v, val)
#endif
