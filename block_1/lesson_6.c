#include <stdio.h>

int main() {
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
