#include "dict.h"
#include "image.h"
#include "option.h"
#include <stdio.h>

void c2t() {
  clearConsole();
  printf("Welcome to c2t\n");
}

int main() {
  struct hashmap *dict = dict_generator();
  if (dict == NULL) {
    fprintf(stderr, "Failed to create dictionary\n");
    return 1;
  }

  char *opt[] = {"translate c to ซี", "translate ซี to c", "add word to dict",
                 "END"};
  int opt_s = selectOptions(opt, sizeof(opt) / sizeof(opt[0]));

  if (opt_s == 1) {
    c2t();
  }

  printf("End of Program!");

  hashmap_free(dict);
  return 0;
}
