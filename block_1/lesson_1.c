#include <stdio.h>

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
  int num = 33777;
  char str = 'X';

  printBin(num);
  printBin(str);

  printf("\n\nDesiatkova:\n%d\n%d", num, str);
  printf("\n\nSestnastkova:\n%x\n%x", num, str);

  return 0;
}
