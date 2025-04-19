#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int GREEN_COLOR = 32;
const int YELLOW_COLOR = 33;
const int BLUE_COLOR = 34;

char *colorized(char *str, int color) {
  char color_start[10];
  char color_end[10];

  static char buffer[sizeof(str) + sizeof(color_start) + sizeof(color_end)];

  sprintf(color_start, "\033[%dm", color);
  sprintf(color_end, "\033[0m");

  buffer[0] = '\0';
  strcat(buffer, color_start);
  strcat(buffer, str);
  strcat(buffer, color_end);

  return buffer;
}

void ex_5_1() {
  for (int i = 0; i < 10; i++) {
    int color;

    if (i <= 3) {
      color = GREEN_COLOR;
    } else if (3 < i && i <= 6) {
      color = YELLOW_COLOR;
    } else {
      color = BLUE_COLOR;
    }

    printf(colorized("%03d", color), i);
    printf("\n");
  }
}

int main() {
  ex_5_1();

  return 0;
}