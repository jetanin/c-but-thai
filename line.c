#include "dict.h"
#include "hashmap.h"

#include <stdio.h>

char *process_line(char *line, struct hashmap *dict) {
  int i = 0;
  int j = 0;
  static char processed[1024];

  struct word_dict *word;

  while (line[i] != '\0') {
    if (line[i] == ' ') {
      j += sprintf(&processed[j], "[SPACE]");
    } else if (line[i] == '\n') {
      j += sprintf(&processed[j], "[NEWLINE]");
    } else {
      processed[j++] = line[i];
      printf("%s\n", &line[i]);
    }
    i++;
  }
  processed[j] = '\0';
  return processed;
}
