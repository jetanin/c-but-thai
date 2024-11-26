#include "dict.h"
#include "image.h"
#include "line.h"
#include "option.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void c2t();
void t2c();
void add_dict();
void search_word();
void list_all_word();

int main() {
  char *opt[] = {"1. Translate c to ซี",
                 "2. Translate ซี to c",
                 "3. Add word to dict",
                 "4. Search for word and definition",
                 "5. List all word and definition",
                 "END"};
  int opt_s = selectOptions(opt, sizeof(opt) / sizeof(opt[0]));

  if (opt_s == 1) {
    c2t();
  }

  if (opt_s == 4) {
    search_word();
  }

  if (opt_s == 5) {
    list_all_word();
  }

  sleep(1);
  printf("End of Program!");

  return 0;
}

void c2t() {
  clearConsole();

  printf("Welcome to c2t\n");
  printf("Enter files name : ");

  char fname[256];
  fgets(fname, sizeof(fname), stdin);
  fname[strcspn(fname, "\n")] = 0;

  FILE *fptr, *foutptr;
  fptr = fopen(fname, "r");

  if (fptr == NULL) {
    perror("Error opening file");
    return;
  }

  char foutputname[256];
  strcpy(foutputname, fname);
  char *dot = strrchr(foutputname, '.');
  if (dot != NULL) {
    strcpy(dot, ".ซี");
  } else {
    strcat(foutputname, ".ซี");
  }

  foutptr = fopen(foutputname, "w");
  if (foutptr == NULL) {
    perror("Error opening output file");
    fclose(fptr);
    return;
  }

  struct hashmap *dict = dict_generator();

  char line[256];
  while (fgets(line, sizeof(line), fptr)) {
    char *processed = process_line(line, dict);
    fputs(processed, foutptr);
  }

  free(dict);
  fclose(foutptr);
  fclose(fptr);
}

void search_word() {
  struct hashmap *dict = dict_generator();

  clearConsole();
  char word[256];
  printf("Enter word to search: ");
  fgets(word, sizeof(word), stdin);
  word[strcspn(word, "\n")] = 0;

  struct word_dict *word_d;

  word_d = hashmap_get(dict, &(struct word_dict){.word = word});

  if (word_d != NULL) {
    printf("Translation: %s\n", word_d->translate);
  } else {
    printf("Word not found in dictionary.\n");
  }

  free(dict);
}

void list_all_word() { clearConsole(); }
