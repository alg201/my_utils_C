#include "vector.h"
vectorgenerator(float);
//test for vector
int main() {
  vector_float *v = create_vector_float();
  if(!v) exit(-1);
  for (float i = 0; i < 1; i += 0.1) {
    append_float(v, i);
  }

  for (size_t i = 0; i < v->len; i++) {
    printf("%f\n", v->data[i]);
  }

  printf("=======================\n");
  remove_index_float(v, (size_t)3);

  for (size_t i = 0; i < v->len; i++) {
    printf("%f\n", v->data[i]);
  }

  printf("=======================\n");
  remove_item_float(v, (float)0.5);

  for (size_t i = 0; i < v->len; i++) {
    printf("%f\n", v->data[i]);
  }

  printf("=======================\n");
  free(v->data);
  free(v);

  return 0;
}
