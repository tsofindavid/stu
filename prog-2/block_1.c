

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

int lesson_1() {
  int num = 33777;
  char str = 'X';

  printBin(num);
  printBin(str);

  printf("\n\nDesiatkova:\n%d\n%d", num, str);
  printf("\n\nSestnastkova:\n%x\n%x", num, str);

  return 0;
}

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

int lesson_2() {
  int num, step, dir;

  printf("\nnumber: ");
  scanf("%iu", &num);

  printf("\nstep size: ");
  scanf("%iu", &step);

  printf("\ndiraction (0-left; 1-right): ");
  scanf("%iu", &dir);

  if (dir > 1) {
    printf("\nStep size can be 0 or 1");
    return lesson_2();
    return lesson_2();
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

int lesson_3() {
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

int lesson_6() {
  const unsigned short input_data_size = 256;
  const unsigned short input_bytes_size = 4 * 2;
  const unsigned short input_address_size = 4 * 4;
  const unsigned short input_record_size = 4 * 2;
  const unsigned short input_checksum_size = 4 * 2;
  const unsigned short input_size = 1 + input_data_size + input_bytes_size +
                                    input_address_size + input_record_size +
                                    input_checksum_size;

  char input[input_size];

  printf("Enter the hex: ");
  scanf("%s", input);

  if (input[0] != ':') {
    printf("Invalid record (missing ':').\n");
    return 1;
  }

  printf("\nOutput: ");

  unsigned int byteCount, address, recordType;

  sscanf(input + 1, "%2x%4x%2x", &byteCount, &address, &recordType);

  unsigned int check_sum = byteCount + address + recordType;

  for (int i = 9; i < (9 + (byteCount * 2)); i += 2) {
    char bytes[2] = {input[i], input[i + 1]};

    unsigned int byte;

    sscanf(bytes, "%2x", &byte);

    printf("%x", byte);

    check_sum += byte;
  }

  printf("%x\n", (-check_sum) & 0xFF);

  return 0;
}

int main() {
  printf("\nLesson_1");
  lesson_1();

  printf("\nLesson_2");
  lesson_2();

  printf("\nLesson_3");
  lesson_3();

  printf("\nLesson_6");
  lesson_6();

  return 0;
}