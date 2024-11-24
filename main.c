#include "dict.h"
#include <stdio.h>

int main() {
  struct hashmap *dict = dict_generator();
  if (dict == NULL) {
    fprintf(stderr, "Failed to create dictionary\n");
    return 1;
  }

  struct word_dict *result =
      (struct word_dict *)hashmap_get(dict, &(struct word_dict){.word = "["});
  if (result) {
    printf("Word: %s, Translation: %s\n", result->word, result->translate);
  } else {
    printf("Word not found\n");
  }

  hashmap_free(dict);

  return 0;
}
