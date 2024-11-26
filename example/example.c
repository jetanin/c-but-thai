#include <stdio.h>

int add(int a, int b) { return a + b; }

int main() {
  printf("hello world!");
  int a = 1, b = 2;
  printf("%d", add(a, b));
  return 0;
}
