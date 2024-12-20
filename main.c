#include "dict.h"
#include "image.h"
#include "line.h"
#include "option.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void translate(int invert);
void search_word();
void list_all_word();
void add_word();
void delete_word();

int main() {
  setlocale(LC_ALL, "th_TH.UTF-8");
  char *opt[] = {"1. Translate c to ซี",
                 "2. Translate ซี to c",
                 "3. Add word to dict",
                 "4. Search for word and definition",
                 "5. List all word and definition",
                 "6. Delete word in dict",
                 "END"};
  int opt_s = selectOptions(opt, sizeof(opt) / sizeof(opt[0]));

  switch (opt_s) {
  case 1:
    translate(0);
    break;
  case 2:
    translate(1);
    break;
  case 3:
    add_word();
    break;
  case 4:
    search_word();
    break;
  case 5:
    list_all_word();
    break;
  case 6:
    delete_word();
    break;
  default:
    printf("Invalid option selected.\n");
    break;
  }

  printf("End of Program!");

  return 0;
}

void translate(int invert) {
  setlocale(LC_ALL, "th_TH.UTF-8");
  clearConsole();

  if (invert) {
    print_t2c();
    printf("\n");
    printf("Welcome to t2c\n");
  } else {
    print_c2t();
    printf("\n");
    printf("Welcome to c2t\n");
  }

  printf("Enter files name : ");

  char fname[256];
  fgets(fname, sizeof(fname), stdin);
  fname[strcspn(fname, "\n")] = 0;

  char *ext = strrchr(fname, '.');
  if (invert) {
    if (ext == NULL || strcmp(ext, ".ซี") != 0) {
      fprintf(
          stderr,
          "Error: Input file must have .ซี extension for t2c translation.\n");
      return;
    }
  } else {
    if (ext == NULL || strcmp(ext, ".c") != 0) {
      fprintf(
          stderr,
          "Error: Input file must have .c extension for c2t translation.\n");
      return;
    }
  }

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
    if (invert) {
      strcpy(dot, "_i.c");
    } else {
      strcpy(dot, ".ซี");
    }
  } else {
    if (invert) {
      strcat(foutputname, "_i.c");
    } else {
      strcat(foutputname, ".ซี");
    }
  }

  foutptr = fopen(foutputname, "w");
  if (foutptr == NULL) {
    perror("Error opening output file");
    fclose(fptr);
    return;
  }

  struct hashmap *dict;
  dict = dict_generator(invert);

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
  struct hashmap *dict = dict_generator(1);

  clearConsole();
  print_search();

  char word[256];
  printf("Enter word to search: ");
  fgets(word, sizeof(word), stdin);
  word[strcspn(word, "\n")] = 0;

  struct word_dict *word_d;

  word_d =
      (struct word_dict *)hashmap_get(dict, &(struct word_dict){.word = word});

  if (word_d != NULL) {
    printf("Translation: %s\n", word_d->translate);
  } else {
    printf("Word not found in dictionary.\n");
  }

  free(dict);
}

void list_all_word() {
  clearConsole();
  print_dict();
  printf("\n");
  FILE *ptr = fopen("dict/dict.txt", "r");
  FILE *ptr_extra = fopen("dict/extra.txt", "r");
  if (ptr == NULL && ptr_extra == NULL) {
    printf("no such file.\n");
    return;
  }

  char word[100];
  char translate[100];

  printf("\nList default dictionary\n");
  if (ptr != NULL) {
    while (fscanf(ptr, "%s %s", word, translate) == 2) {
      printf("%s : %s \n", word, translate);
    }
    fclose(ptr);
  }

  printf("\nList extra dictionary\n");
  if (ptr_extra != NULL) {
    while (fscanf(ptr_extra, "%s %s", word, translate) == 2) {
      printf("%s : %s \n", word, translate);
    }
    fclose(ptr_extra);
  }
}

void add_word() {
  clearConsole();
  print_add();
  printf("\n");

  FILE *file;
  file = fopen("dict/extra.txt", "a");

  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char word[256];
  char translation[256];

  printf("Enter word: ");
  fgets(word, sizeof(word), stdin);
  word[strcspn(word, "\n")] = 0;

  printf("Enter translation: ");
  fgets(translation, sizeof(translation), stdin);
  translation[strcspn(translation, "\n")] = 0;

  fprintf(file, "%s %s\n", word, translation);
  fclose(file);
  printf("Word added successfully.\n");
}

void delete_word() {
  clearConsole();
  print_delete();
  printf("\n");

  char word[256];
  printf("Enter word to delete: ");
  fgets(word, sizeof(word), stdin);
  word[strcspn(word, "\n")] = 0;

  FILE *file = fopen("dict/extra.txt", "r");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  FILE *temp = fopen("dict/temp.txt", "w");
  if (temp == NULL) {
    perror("Error opening temporary file");
    fclose(file);
    return;
  }

  char line[512];
  int found = 0;
  while (fgets(line, sizeof(line), file)) {
    char *pos = strchr(line, ' ');
    if (pos != NULL) {
      *pos = '\0';
      if (strcmp(line, word) != 0) {
        *pos = ' ';
        fputs(line, temp);
      } else {
        found = 1;
      }
    }
  }

  fclose(file);
  fclose(temp);

  if (found) {
    remove("dict/extra.txt");
    rename("dict/temp.txt", "dict/extra.txt");
    printf("Word deleted successfully.\n");
  } else {
    remove("dict/temp.txt");
    printf("Word not found in dictionary.\n");
  }
}
