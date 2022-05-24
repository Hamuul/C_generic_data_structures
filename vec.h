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

#define vec_truncate(v, len)\
    ((v)->length = (len) < (v)->length ? (len) : (v)->length)


#define vec_clear(v)\
    ((v)->length = 0)


#define vec_first(v)\
    (v)->data[0]


#define vec_last(v)\
    (v)->data[(v)->length - 1]

#define vec_reserve(v, n)\
    vec_reserve_(v_unpack_(v), n)

#define vec_compact(v)\
    vec_compact_(vec_unpack_(v))


#define vec_pusharr(v, arr, count)\
  do {\
    int i__, n__ = (count);\
    if (vec_reserve_po2_(vec_unpack_(v), (v)->length + n__) != 0) break;\
    for (i__ = 0; i__ < n__; i__++)\
    {\
         (v)->data[(v)->length++] = (arr)[i__];\
    }\
  }while(0)

#define vec_concat(v, v2)\
  vec_pusharr((v), (v2)->data, (v2)->length)

#define vec_find(v, val, idx)\
  do {\
      for((idx) = 0; (idx) < (v)->length; (idx)++)\
      {\
          if((v)->data[(idx)] == (val))\
            break;\
      }\
      if ((idx) == (v)->length)\
        (idx) = -1;\
  }while(0)

#define vec_remove(v, val)\
  do {\
      int idx__;\
      vec_find(v, val, idx__);\
      if(idx != -1)\
        vec_splice(v, idx__, 1);\
  }while(0)
int vec_expand_(char **data, int *length, int *capacity, int memsz);
int vec_reserve_(char **data, int *length, int *capacity, int memsz, int n);
int vec_insert_(char **data, int *length, int *capacity, int memsz, int idx);
void vec_splice_(char **data, int *length, int *capacity, int memsz,
                 int start, int count);
void vec_swap_(char **data, int *length, int *capacity, int memsz,
               int idx1, int idx2);

typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(float) vec_float_t;
typedef vec_t(double) vec_double_t;
#endif
