#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int KEY_ESC = 27;
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
int main() {
  lesson_6();

  return 0;
}