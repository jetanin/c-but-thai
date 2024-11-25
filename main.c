#include "dict.h"
#include "image.h"
#include "line.h"
#include "option.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

int main() {
  char *opt[] = {"translate c to ซี", "translate ซี to c", "add word to dict",
                 "END"};
  int opt_s = selectOptions(opt, sizeof(opt) / sizeof(opt[0]));

  if (opt_s == 1) {
    c2t();
  }

  sleep(2);
  // clearConsole();
  printf("End of Program!");

  return 0;
}
