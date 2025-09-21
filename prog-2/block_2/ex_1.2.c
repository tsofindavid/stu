#include <stdio.h>

int main() {
  int value = 4;
  int result;

  __asm__("shl %1, 1\n\t"
          "mov %0, %1\n\t"
          : "=r"(result)
          : "r"(value)

  );

  printf("result: %d\n", result);
  return 0;
}
