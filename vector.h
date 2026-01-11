#pragma once
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * vectorgenerator(type)
 * Generates a dynamic vector (like std::vector from C++) which type is indicated in `type` parameter
 *
 * Generates:
 *  - typedef struct {
 *      type *data;
 *      int len;
 *    } vector_type; 
 *
 *  - Functions:
 *    vector_type *create_vector_type();
 *      - Creates an empty vector. vector.data points to nullptr until data is assigned.
 *    vector_type *resize_vector_type(vector_type *v, size_t bytes);
 *      - Resizes the vector adding the bytes that recives as second argument. If vector.data points to nullptr, the allocates recived bytes on memory.
 *    vector_type *append_type(vector_type *v, type item);
 *      - Appends item into the vector and resizes it if necessary.
 *    size_t indexof_type(vector_type *v, type item);
 *      - Locates and returns the index of the item. In case the item couldn't be found, returns INDEX_NOT_FOUND.
 *    vector_type *remove_index_type(vector_type *v, size_t index);
 *      - Removes the item given the index, then shrinks the vector. In case the index is not found, the function does nothing 
 *    vector_type *remove_item_type(vector_type *v, type index);
 *      - Removes the item on the vector. In case this item couldn't be found, the function does nothing
 *    void destroy_vector_type(vector_type *v);
 *      - Destroys the vector and frees the memory. This doesn't free the memory of the data inside. (If the vector is storing pointers, the memory of the data which is pointed by this, isn't free, should be done manually)
 *    void destroy_data_type(vector_type *v);
 *      - Destroys all the data inside v. This should be use in case the data inside of the vector is a pointer. For example, if you have vector_string, the data inside is type string (aka char*) so, to be able to free correctly, you should be using this function. In case is a int or any primitive data which is not a pointer, this function will cause SEGFAULT. If v is nullptr, this function does nothing.
 */

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
      v->data = malloc(bytes); 				       	               \
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
      if (memcmp(&v->data[i], &item, sizeof(type)) == 0)     		       \
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
    size_t newsize = sizeof(type) * v->len;                                    \
    v->data = realloc(v->data, newsize);        			       \
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
  }                                                                            \
                                                                               \
  void destroy_data_##type(vector_##type *v){                                  \
    if(!v) return;                                                             \
    for(int i = 0; i < v->len; ++i){                                           \
      if (!v->data[i]) continue;            				       \
      free(v->data[i]);                                                        \
    }                                                                          \
  }                                                                            
#define INDEX_NOT_FOUND ((size_t)-1)
typedef char* string;
