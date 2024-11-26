#ifndef DICT_H
#define DICT_H

#include "hashmap.h"
#include <stdint.h>

struct word_dict {
  char *word;
  char *translate;
};

int word_compare(const void *a, const void *b, void *udata);
uint64_t word_hash(const void *item, uint64_t seed0, uint64_t seed1);
struct hashmap *dict_generator();
struct hashmap *dict_generator_invert();

#endif // DICT_H
