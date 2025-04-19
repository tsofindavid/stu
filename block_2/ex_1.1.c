#include <stdio.h>

int main() {
  int a = 5;
  int b = 7;
  int result;

  __asm__("mov eax, %1;"
          "add eax, %2;"
          "mov %0, eax;"
          : "=r"(result)
          : "r"(a), "r"(b)
          : "eax");

  printf("result: %d\n", result);
  return 0;
}
