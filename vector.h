#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define vectorgenerator(type)                                                  \
                                                                               \ 
typedef struct {                                                               \
    type *data;                                                                \
    int len;                                                                   \
  } vector_##type;                                                             \
                                                                               \
  vector_##type *create_vector_##type() {                                      \
    vector_##type *v = malloc(sizeof(vector_##type));                          \
    v->data = NULL;                                                            \
    v->len = 0;                                                                \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  vector_##type *resize_vector_##type(vector_##type *v, size_t bytes) {        \
    if (v->data == NULL) {                                                     \
      v->data = malloc(sizeof(type));                                          \
      return v;                                                                \
    }                                                                          \
    size_t actualSize = sizeof(type) * v->len;                                 \
    v->data = realloc(v->data, actualSize + bytes);                            \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  vector_##type *append_##type(vector_##type *v, type val) {                   \
    v = resize_vector_##type(v, sizeof(type));                                 \
    v->data[v->len] = val;                                                     \
    v->len++;                                                                  \
                                                                               \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  size_t indexof_##type(vector_##type *v, type item) {                         \
    for (int i = 0; i < v->len; ++i) {                                         \
      if (v->data[i] == item)                                                  \
        return i;                                                              \
    }                                                                          \
    return INDEX_NOT_FOUND;                                                    \
  }                                                                            \
                                                                               \
  vector_##type *remove_index_##type(vector_##type *v, size_t index) {         \
    if (index > v->len - 1)                                                    \
      return v;                                                                \ 
    memcpy(v->data + (index), v->data + (index + 1),                           \
           ((v->len - 1) - index) *                                            \
             sizeof(type)); /* moves data: index - (len-1) bytes to {index ..  \
                               len-2} */                                       \
    memset(v->data + (v->len - 1), 0x0,                                        \
           sizeof(type)); /* clear residual data */                            \
    v->len -= 1;                                                               \
    return v;                                                                  \
  }                                                                            \
                                                                               \
  vector_##type *remove_item_##type(vector_##type *v, type i) {                \
    size_t index = indexof_##type(v, i);                                       \
    if (index == INDEX_NOT_FOUND)                                              \
      return v;                                                                \
    return remove_index_##type(v, index);                                      \
  }                                                                            \
                                                                               \
  void destroy_vector_##type(vector_##type *v) {                               \
    if(!v) return;                                                             \
    free(v->data);                                                             \
    free(v);                                                                   \
  }

#define INDEX_NOT_FOUND -1