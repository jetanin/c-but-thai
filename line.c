#include "dict.h"
#include "hashmap.h"
#include <string.h>

#include <stdio.h>

int check_indent(char *line) {
  int indent_level = 0;
  while (*line == ' ' || *line == '\t') {
    if (*line == ' ') {
      indent_level++;
    } else if (*line == '\t') {
      indent_level += 4;
    }
    line++;
  }
  return indent_level;
}

char *process_line(char *line, struct hashmap *dict) {
  static char processed[4096];
  int line_indent = check_indent(line);

  int i = 0;
  char *p = strtok(line, " ");
  char *array[4096];

  while (p != NULL) {
    array[i++] = p;
    p = strtok(NULL, " ");
  }

  struct word_dict *word;

  sprintf(processed, "%*s", line_indent, "");
  for (int j = 0; j < i; j++) {
    word = hashmap_get(dict, &(struct word_dict){.word = array[j]});
    printf(array[j]);
    if (word != NULL) {
      sprintf(processed + strlen(processed), "%s ", word->translate);
    } else {
      sprintf(processed + strlen(processed), "%s ", array[j]);
    }
  }
  if (strlen(processed) > 0 && processed[strlen(processed) - 1] == ' ') {
    processed[strlen(processed) - 1] = '\0';
  }

  return processed;
}
