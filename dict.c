#include "hashmap.h"
#include <stdio.h>
#include <string.h>

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

struct hashmap *dict_generator() {
  struct hashmap *map = hashmap_new(sizeof(struct word_dict), 0, 0, 0,
                                    word_hash, word_compare, NULL, NULL);

  struct word_dict wd1 = {"hello", "สวัสดีครับ"};
  struct word_dict wd2 = {"world", "คำพูด"};

  hashmap_set(map, &wd1);
  hashmap_set(map, &wd2);

  return map;
}
