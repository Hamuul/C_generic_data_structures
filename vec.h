#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <string.h>

#define vec_unpack_(v)\
    (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)

/* Creates a vec struct for containing values of type T. */
#define vec_t(T)\
    struct {T* data; int length, capacity;}

/* Initialises the vector, this must be called before the vector can be used.*/
#define vec_init(v)\
    memset((v), 0, sizeof(*(v)))

/* Deinitialises the vector, freeing the memory the vector allocated during use;
   this should be called when we're finished with a vector. */
#define vec_deinit(v)\
    ( free((v))->data,\
      vec_init(v) )

/**
    *Pushes a value to the end of the vector.
    *Returns 0 if the operation was successful, otherwise -1 is returned
    *and the vector remains unchanged.
**/
#define vec_push(v, val)\
    ( vec_expand_(vec_unpack_(v)) ? -1 :\
      ((v)->data[(v)->length++] = (val), 0), 0)

/* Removes and returns the value at the end of the vector. */
#define vec_pop(v)\
    (v)->data[--(v)->length];

/* Removes the number of values specified by count, starting at the index start. */
#define vec_splice(v, start, count)\
    ( vec_splice_(vec_unpack_(v), start, count)),\
      (v)->length -= count )

/**
    *Inserts the value val at index idx shifting the elements
    *after the index to make room for the new value.
    *Returns 0 if the operation was successful,
    *otherwise -1 is returned and the vector remains unchanged.
**/
#define vec_insert(v, idx, val)\
    ( vec_insert_(vec_unpack_(v), idx)) ? -1 :\
      ((v)->data[idx] = (val), 0), (v)->length++, 0)

/* Sorts the values of the vector;
   cmp should be a qsort-compatible compare function. */
#define vec_sort(v, cmp)\
    qsort((v)->data, (v)->length, sizeof(*(v)->data), cmp)

/* Swaps the values at the indices idx1 and idx2 with one another. */
#define vec_swap(v, idx1, idx2)\
    vec_swap_(vec_unpack_(v), idx1, idx2)

/* Truncates the vector's length to len */
#define vec_truncate(v, len)\
    ((v)->length = (len) < (v)->length ? (len) : (v)->length)


#define vec_first(v)\
    (v)->data[0]


#define vec_last(v)\
    (v)->data[(v)->length - 1]

/**
    *Reserves capacity for at least n elements in the given vector;
    *if n is less than the current capacity then vec_reserve() does nothing.
    *Returns 0 if the operation was successful,
    *otherwise -1 is returned and the vector remains unchanged.
**/
#define vec_reserve(v, n)\
    vec_reserve_(v_unpack_(v), n)

/**
    *Reduces the vector's capacity to the smallest size required to store
    *its current number of values.
    *Returns 0 if the operation is successful,
    *otherwise -1 is returned and the vector remains unchanged.
**/
#define vec_compact(v)\
    vec_compact_(vec_unpack_(v))

/* Pushes the contents of the array arr to the end of the vector.
   count should be the number of elements in arr. */
#define vec_pusharr(v, arr, count)\
  do {\
    int i__, n__ = (count);\
    if (vec_reserve_po2_(vec_unpack_(v), (v)->length + n__) != 0) break;\
    for (i__ = 0; i__ < n__; i__++)\
    {\
         (v)->data[(v)->length++] = (arr)[i__];\
    }\
  }while(0)

/* Append v2 to the end of v */
#define vec_concat(v, v2)\
  vec_pusharr((v), (v2)->data, (v2)->length)

/**
   *Finds the first occurrence of the value val in the vector.
   *idx should be the position where val was first found;
   *idx is set to -1 if val could not be found in the vector.
**/
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

/* Remove first occurence of val from v. */
#define vec_remove(v, val)\
  do {\
      int idx__;\
      vec_find(v, val, idx__);\
      if(idx != -1)\
        vec_splice(v, idx__, 1);\
  }while(0)

/* Reverse v in-place. */
#define vec_reverse(v)\
    do {\
        int i__ = (v)->length / 2;\
        while(i__--)\
        {\
                vec_swap((v), i__, (v)->length - (i__ + 1));\
        }\
    }while(0)

int vec_expand_(char **data, int *length, int *capacity, int memsz);
int vec_reserve_(char **data, int *length, int *capacity, int memsz, int n);
int vec_reserve_po2_(char **data, int *length, int *capacity, int memsz, int n);
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
