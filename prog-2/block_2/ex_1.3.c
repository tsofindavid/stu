#include <stdio.h>

int main() {
  char result;
  int a = 5;

  __asm__ __volatile__(
      "movl %1, %%eax;"  // кладем число в eax
      "cmpl $10, %%eax;" // сравниваем с 10
      "jl 1f\n\t"        // если меньше, прыжок на метку 1
      "addl $55, %%eax;" // если больше или равно — добавь 55 → 'A' и т.д.
      "jmp 2f\n\t"       // прыжок на конец
      "1:\n\t"
      "addl $48, %%eax;" // если < 10 — добавь 48 → '0' и т.д.
      "2:\n\t"
      "movb %%al, %0;" // записываем только младший байт (char)
      : "=r"(ch)       // выход
      : "r"(num)       // вход
      : "%eax"         // испорченный регистр
  );

  printf("result: %d\n", result);
  return 0;
}
