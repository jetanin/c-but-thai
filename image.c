#include <stdio.h>
#define MAX_LEN 128

void print_image(FILE *fptr);
int print_from_file(const char *filename);

int print_logo() {
  char *filename = "storage/c-but-thai-logo.txt";
  return print_from_file(filename);
}

int print_dict() { return print_from_file("storage/reload_dict.txt"); }

int print_from_file(const char *filename) {
  FILE *fptr = NULL;

  if ((fptr = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "error opening %s\n", filename);
    return 1;
  }

  print_image(fptr);

  fclose(fptr);

  return 0;
}

void print_image(FILE *fptr) {
  char read_string[MAX_LEN];

  while (fgets(read_string, sizeof(read_string), fptr) != NULL)
    printf("%s", read_string);
}

void clearConsole() {
#ifdef _WIN32
  system("cls");
#else
  printf("\033[H\033[J"); // ANSI escape code for Linux/Unix
#endif
}
