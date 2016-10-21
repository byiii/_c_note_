#include <stdio.h>

int main() {
  int c;
  while((c = getchar()) != EOF) {
    putchar(c);
    printf(" != EOF, value: %d\n", c!=EOF);
  }
  printf("input != EOF, value: %d\n", c!=EOF);

  return 0;
}
