
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAX 1000
#define N 100

char op[N + 1] = "--=--=--=--=--=--=--=--=--=--=--";
// char op[N + 1] = "!!!!) 8Bavi  ?   ma6  /  &^zi4vot.   ? FOREVER.";
char mem[N + 1] = {0};
int sp, ep = 0;

int cmd_out_range() {
  if (sp > ep) {
    printf("ERR_POSITION");
    return 1;
  }

  if (sp == ep) {
    printf("\n");
    return 0;
  }

  for (int i = sp; i < ep; i++) {
    printf("%c", op[i]);
  }

  printf("\n");

  return 0;
}

int cmd_next_find() {
  int len = strlen(op);

  for (int i = sp; i < len; i++) {
    if (isalnum(op[i])) {
      sp = i;
      ep = len;

      for (int x = i; x < len; x++) {
        if (!isalnum(op[x])) {
          ep = x;
          break;
        }
      }

      break;
    }
  }

  return 0;
}

int cmd_next() {
  if (isalnum(op[sp])) {
    sp = sp + 1;
    return cmd_next();
  }

  return cmd_next_find();
}

int cmd_prev_find() {
  ep = sp;

  for (int i = sp; i >= 0; i--) {
    if (isalnum(op[i])) {
      sp = 0;
      ep = i + 1;

      for (int x = i; x >= 0; x--) {
        if (!isalnum(op[x])) {
          sp = x + 1;
          break;
        }
      }
      break;
    }
  }

  return 0;
}

int cmd_prev() {
  if (sp == 0) {
    ep = sp;
    return 0;
  }

  if (isalnum(op[sp])) {
    sp = sp - 1;
    return cmd_prev();
  }

  return cmd_prev_find();
}
int main() {

  for (int i = 0; i < strlen(op); i++) {
    printf("%d ", i);
    printf("%c %d\n", op[i], isalnum(op[i]));
  }

  // sp = 17;

  // cmd_prev();
  // printf("prev:\n");
  // printf("sp: %d\n", sp);
  // printf("ep: %d\n", ep);
  // printf("\n");

  cmd_next();
  printf("next:\n");
  printf("sp: %d\n", sp);
  printf("ep: %d\n", ep);
  printf("\n");

  cmd_out_range();

  return 0;
}