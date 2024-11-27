#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_DICT "dict/dict.txt"

struct word_dict {
  char *word;
  char *translate;
};

int word_compare(const void *a, const void *b, void *udata) {
  const struct word_dict *ua = (const struct word_dict *)a;
  const struct word_dict *ub = (const struct word_dict *)b;
  return strcmp(ua->word, ub->word);
}

uint64_t word_hash(const void *item, uint64_t seed0, uint64_t seed1) {
  const struct word_dict *word = (const struct word_dict *)item;
  return hashmap_sip(word->word, strlen(word->word), seed0, seed1);
}

struct hashmap *dict_generator_common(int invert) {
  struct hashmap *map = hashmap_new(sizeof(struct word_dict), 0, 0, 0,
                                    word_hash, word_compare, NULL, NULL);

  FILE *ptr = fopen(DEFAULT_DICT, "r");
  if (ptr == NULL) {
    printf("no such file.\n");
    return NULL;
  }

  char word[100];
  char translate[100];

  while (fscanf(ptr, "%s %s", word, translate) == 2) {
    struct word_dict *w1 = malloc(sizeof(struct word_dict));
    if (w1 == NULL) {
      printf("Memory allocation failed.\n");
      fclose(ptr);
      return NULL;
    }

    if (invert) {
      w1->word = malloc(strlen(translate) + 1);
      w1->translate = malloc(strlen(word) + 1);
    } else {
      w1->word = malloc(strlen(word) + 1);
      w1->translate = malloc(strlen(translate) + 1);
    }

    if (w1->word == NULL || w1->translate == NULL) {
      printf("Memory allocation failed.\n");
      free(w1->word);
      free(w1->translate);
      free(w1);
      fclose(ptr);
      return NULL;
    }

    if (invert) {
      strcpy(w1->word, translate);
      strcpy(w1->translate, word);
    } else {
      strcpy(w1->word, word);
      strcpy(w1->translate, translate);
    }

    hashmap_set(map, w1);
  }

  fclose(ptr);
  return map;
}

struct hashmap *dict_generator() { return dict_generator_common(0); }

struct hashmap *dict_generator_invert() { return dict_generator_common(1); }
