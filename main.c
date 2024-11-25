#include "dict.h"
#include "image.h"
#include <stdio.h>

int main() {
  struct hashmap *dict = dict_generator();
  if (dict == NULL) {
    fprintf(stderr, "Failed to create dictionary\n");
    return 1;
  }

  print_logo();

  hashmap_free(dict);
  return 0;
}
