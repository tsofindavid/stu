#include <stdio.h>

int countBit(int num) {
  int count = 0;

  for (int i = num; i > 0; i--) {
    if (num > 0) {
      num = num / 2;
      count++;
    } else {
      break;
    }
  }

  return count;
}

void printBin(unsigned int num) {
  const int size = (sizeof(num) * 8);

  unsigned int val = num;
  unsigned int binaries[(sizeof(num) * 8)];

  for (int i = size; i > 0; i--) {
    binaries[i] = val % 2;
    val = val / 2;
  }

  printf("\nBinaries: ");

  for (int i = 1; i <= size; i++) {
    printf("%d", binaries[i]);
  }
}

int main() {
  int num, step, dir;

  printf("\nnumber: ");
  scanf("%iu", &num);

  printf("\nstep size: ");
  scanf("%iu", &step);

  printf("\ndiraction (0-left; 1-right): ");
  scanf("%iu", &dir);

  if (dir > 1) {
    printf("\nStep size can be 0 or 1");
    return main();
  }

  if (step == 0) {
    return num;
  }

  printf("\nIntput: ");
  printBin(num);

  int num_size = countBit(num);

  if (dir == 0) {
    step %= num_size;
    num = (num << step) | ((num & ((1 << step) - 1)) >> (num_size - step));
  }

  if (dir == 1) {
    step %= num_size;
    num = (num >> step) | ((num & ((1 << step) - 1)) << (num_size - step));
  }

  printf("\nOutput: ");
  printBin(num);

  printf("\nOutput norm: %d", num);

  return 0;
}
