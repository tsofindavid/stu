#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const int KEY_ESC = 27;

const int GREEN_COLOR = 32;
const int YELLOW_COLOR = 33;

void display_welcome(int *row) {
  clear();
  *row = 0;
  move(*row, 0);
  refresh();

  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "|         WELCOME TO THE REACTION TEST        |");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Test your reflexes with this simple game!  |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press F1 to view the usage instructions.   |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press F2 to start the reaction test.       |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press ESC or F10 to exit the program.      |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  refresh();
}

void display_instructions(int *row) {
  clear();
  *row = 0;
  move(*row, 0);
  refresh();

  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "|           PROGRAM USAGE INSTRUCTIONS        |");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|  F1  | Display this usage instruction       |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  F2  | Start the measurement process        |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  ESC | Exit the program                     |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  F10 | Exit the test                        |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  MEASUREMENT PROCESS:                       |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  1. A random letter will appear in the      |");
  *row = *row + 1;
  mvprintw(*row, 0, "|     center of the window.                   |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  2. Press the same letter to stop the timer.|");
  *row = *row + 1;
  mvprintw(*row, 0, "|  3. The program will display the elapsed    |");
  *row = *row + 1;
  mvprintw(*row, 0, "|     time in seconds.                        |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  4. Incorrect key presses will be ignored.  |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  5. After each measurement, a new letter    |");
  *row = *row + 1;
  mvprintw(*row, 0, "|     will be generated, and the process      |");
  *row = *row + 1;
  mvprintw(*row, 0, "|     repeats until you exit.                 |");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press F1 to hide this instruction and      |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  continue using the program.                |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  refresh();
}

void display_result(int *row, int *pressed, int pressed_count) {
  clear();
  *row = 0;
  move(*row, 0);
  refresh();

  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "|           MEASUREMENT RESULTS               |");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Pressed keys:                             |");
  *row = *row + 1;
  for (int i = 0; i < pressed_count; i++) {
    mvprintw(*row, 0, "%c", (char)pressed[i]);
    *row = *row + 1;
  }
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press ESC to exit the program.             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  refresh();
}
void lesson_6() {
  int mrow, mcol;

  int pressed[100] = {};
  int pressed_count = 0;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  idlok(stdscr, TRUE);

  getmaxyx(stdscr, mrow, mcol);

  int prev_key = 0;
  clock_t press_time = 0;
  clock_t start_time = 0;

  int key;
  int end = 0;
  int row = 0;

  display_welcome(&row);

  while (!end) {
    if (row > mrow) {
      clear();
      row = 0;
      move(row, 0);
    }

    refresh();
    key = getch();

    switch (key) {
    case KEY_F(1):
      display_instructions(&row);
      break;
    case KEY_F(2):
      mvprintw(row++, 0, "Test started...");
      start_time = clock();
      break;
    case KEY_ESC:
      end = 1;
      break;
    case KEY_F(10):
      display_result(&row, pressed, pressed_count);
      break;
    default:

      if (start_time == 0) {
        break;
      }

      if (prev_key == 0) {
        prev_key = key;
        break;
      }

      if (prev_key == key) {
        if (pressed[pressed_count - 1] != key) {
          pressed[pressed_count] = key;
          pressed_count++;
        }

        mvprintw(row++, 0, "key %c pressed: %2.f", (char)key,
                 (float)((clock() - start_time)));
      } else {
        prev_key = 0;
      }

      break;
    }
  }
  endwin();
}
long max_str(char *arr[], int count) {
  int max = 0;
  for (int i = 0; i < count; i++) {
    int len = strlen(arr[i]);
    if (len > max)
      max = len;
  }
  return max;
}

char *gen_str(char symbol, int size) {
  char *str = malloc(size + 1);

  for (int i = 0; i < size; i++) {
    str[i] = symbol;
  }

  str[size] = '\0';

  return str;
}

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

void lesson_3() {
  char *title = "Array 001";

  char *name_title = "Name";
  char *name = "David Tsofin asdasdasdasd";

  char *height_title = "Height";
  char *height = "175cm";

  char *wight_title = "Weight";
  char *weight = "85kg";

  char *phone_title = "Phone";
  char *phone = "0950 710 314";

  int rows = 2;
  int columns = 3;

  int title_width = max_str(
      (char *[]){name_title, height_title, phone_title, wight_title}, 4);

  int value_width = max_str((char *[]){name, height, phone, weight}, 4);

  int pad = (title_width + value_width + 1 - strlen(title)) / 2;

  printf(colorized("+- ", YELLOW_COLOR));
  printf(colorized("%*s%s%*s", GREEN_COLOR), pad, "", title, pad, "");
  printf(colorized(" -+\n", YELLOW_COLOR));

  printf(colorized("+-%*s-+-%*s-+\n", YELLOW_COLOR), title_width,
         gen_str('-', title_width), value_width, gen_str('-', value_width));

  printf(colorized("| ", YELLOW_COLOR));
  printf(colorized("%-*s", GREEN_COLOR), title_width, name_title);
  printf(colorized(" | ", YELLOW_COLOR));
  printf(colorized("%*s", GREEN_COLOR), value_width, name);
  printf(colorized(" |\n", YELLOW_COLOR));

  printf(colorized("| ", YELLOW_COLOR));
  printf(colorized("%-*s", GREEN_COLOR), title_width, height_title);
  printf(colorized(" | ", YELLOW_COLOR));
  printf(colorized("%*s", GREEN_COLOR), value_width, height);
  printf(colorized(" |\n", YELLOW_COLOR));

  printf(colorized("| ", YELLOW_COLOR));
  printf(colorized("%-*s", GREEN_COLOR), title_width, wight_title);
  printf(colorized(" | ", YELLOW_COLOR));
  printf(colorized("%*s", GREEN_COLOR), value_width, weight);
  printf(colorized(" |\n", YELLOW_COLOR));

  printf(colorized("| ", YELLOW_COLOR));
  printf(colorized("%-*s", GREEN_COLOR), title_width, phone_title);
  printf(colorized(" | ", YELLOW_COLOR));
  printf(colorized("%*s", GREEN_COLOR), value_width, phone);
  printf(colorized(" |\n", YELLOW_COLOR));

  printf(colorized("+-%*s-+-%*s-+\n", YELLOW_COLOR), title_width,
         gen_str('-', title_width), value_width, gen_str('-', value_width));
}

void display_player(int *row) {
  clear();
  *row = 0;
  move(*row, 0);
  refresh();

  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "|         WELCOME TO THE REACTION TEST        |");
  *row = *row + 1;
  mvprintw(*row, 0, "|                                             |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Test your reflexes with this simple game!  |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press F1 to play.                          |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press F2 to pause.                         |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press F3 to stop.                          |");
  *row = *row + 1;
  mvprintw(*row, 0, "|  Press ESC                                  |");
  *row = *row + 1;
  mvprintw(*row, 0, "+---------------------------------------------+");
  *row = *row + 1;
  refresh();
}

void lesson_4() {
  pid_t pid;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  int key;
  int end = 0;
  int row = 0;

  display_player(&row);

  while (!end) {
    refresh();
    key = getch();

    switch (key) {
    case KEY_F(1):
      play(&pid, "demo.mp3");
      break;
    case KEY_F(2):
      // pause(&pid);
      break;
    case KEY_F(3):
      // stop(&pid);
      break;
    case KEY_ESC:
      end = 1;
      break;
    default:
      break;
    }
  }
  endwin();
}

int main() {
  // lesson_3();
  lesson_4();
  // lesson_6();

  return 0;
}