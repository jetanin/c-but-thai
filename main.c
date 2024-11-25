#include "dict.h"
#include "option.h"
#include <stdio.h>

int main() {
  struct hashmap *dict = dict_generator();
  if (dict == NULL) {
    fprintf(stderr, "Failed to create dictionary\n");
    return 1;
  }

  char *opt[] = {"translate c to ซี", "translate ซี to c", "add word to dict",
                 "END"};
  int t = selectOptions(opt, 4);

  hashmap_free(dict);
  return 0;
}
