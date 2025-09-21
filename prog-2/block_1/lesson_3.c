#include <stdio.h>

int main() {
  int num;

  printf("\nEnter the number: ");
  scanf("%d", &num);

  int count_one = 0;

  for (int i = 0; i < (sizeof(num) * 8); i++) {
    if ((num >> i) & 1) {
      count_one++;
    }
  }

  printf("Count of 1: %d\n", count_one);

  return 0;
}