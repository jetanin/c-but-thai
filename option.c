#ifdef _WIN32
#include <conio.h> // For Windows
#else
#include <termios.h>
#include <unistd.h>
#endif

#include "image.h"
#include <stdio.h>

int getch() {
#ifdef _WIN32
  return _getch();
#else
  struct termios oldt, newt;
  int ch;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return ch;
#endif
}

void clearConsole() {
#ifdef _WIN32
  system("cls");
#else
  printf("\033[H\033[J"); // ANSI escape code for Linux/Unix
#endif
}

#define UP_ARROW 65
#define DOWN_ARROW 66
#define ENTER 10

void displayMenu(int current, char *opt[], int optSize) {
  clearConsole();
  print_logo();
  printf("Use arrow keys to navigate, and press Enter to select.\n\n");

  for (int i = 0; i < optSize; i++) {
    printf("%s%s\n", current == i + 1 ? "> " : "  ", opt[i]);
  }
}

int selectOptions(char *opt[], size_t opt_size) {
  int current = 1;
  int key;

  displayMenu(current, opt, opt_size);

  while (1) {
    key = getch();

#ifdef _WIN32
    if (key == 224) { // Special key (arrow key prefix for Windows)
      key = getch();
#endif
      if (key == UP_ARROW) {
        current--;
        if (current < 1)
          current = opt_size;
      } else if (key == DOWN_ARROW) {
        current++;
        if (current > opt_size)
          current = 1;
      }
#ifdef _WIN32
    }
#endif

    if (key == ENTER) {
      printf("\nYou selected Option %d : %s\n", current, opt[current - 1]);
      break;
    }

    displayMenu(current, opt, opt_size);
  }

  return current;
}
