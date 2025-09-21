#include <ao/ao.h>
#include <ctype.h>
#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constants for colors
const int GREEN_COLOR = 32;
const int YELLOW_COLOR = 33;
const int BLUE_COLOR = 34;

// Exercise 1.1
void ex_1_1() {
  int a = 5;
  int b = 7;
  int result;

  __asm__("mov eax, %1;"
          "add eax, %2;"
          "mov %0, eax;"
          : "=r"(result)
          : "r"(a), "r"(b)
          : "eax");

  printf("Exercise 1.1 result: %d\n", result);
}

// Exercise 1.2
void ex_1_2() {
  int value = 4;
  int result;

  __asm__("shl %1, 1\n\t"
          "mov %0, %1\n\t"
          : "=r"(result)
          : "r"(value));

  printf("Exercise 1.2 result: %d\n", result);
}

// Exercise 1.3
void ex_1_3() {
  int num = 13;
  char ch;

  __asm__ __volatile__("movl %1, %%eax\n\t"
                       "cmpl $10, %%eax\n\t"
                       "jl 1f\n\t"
                       "addl $55, %%eax\n\t"
                       "jmp 2f\n\t"
                       "1:\n\t"
                       "addl $48, %%eax\n\t"
                       "2:\n\t"
                       "movb %%al, %0\n\t"
                       : "=r"(ch)
                       : "r"(num)
                       : "%eax");

  printf("Exercise 1.3 num: %d → Hex ASCII ch: %c\n", num, ch);
}

// Exercise 4
#define BUF_SIZE 4096
struct timespec ts = {0, 100 * 1000000}; // 100ms
const int KEY_ESC = 27;
const char *song_dir = "./songs/";
char filename[256] = {0};
ao_device *device;
ao_sample_format format;
size_t read;
char *buffer;
int buf_size;
FILE *fp;
int pause = 1;
int key;
int end = 0;
int row = 0;

void display_player() {
  clear();
  row = 0;
  move(row, 0);
  refresh();

  mvprintw(row++, 0, "+---------------------------------------------+");
  mvprintw(row++, 0, "|         WELCOME TO THE STRANGE PLAYER       |");
  mvprintw(row++, 0, "+---------------------------------------------+");
  mvprintw(row++, 0, "|  Press F1 to list songs.                    |");
  mvprintw(row++, 0, "|  Press F2 to select a song.                 |");
  mvprintw(row++, 0, "|  Press F3 to play.                          |");
  mvprintw(row++, 0, "|  Press F4 to pause.                         |");
  mvprintw(row++, 0, "|  Press F5 to stop.                          |");
  mvprintw(row++, 0, "|  Press ESC to exit.                         |");
  mvprintw(row++, 0, "+---------------------------------------------+");
  mvprintw(row++, 0, "Selected song: %s", filename);

  switch (pause) {
  case 0:
    mvprintw(row++, 0, "State: playing");
    break;
  case 1:
    mvprintw(row++, 0, "State: paused");
    break;
  case 2:
    mvprintw(row++, 0, "State: stopped");
    break;
  default:
    break;
  }

  mvprintw(row++, 0, "+---------------------------------------------+");
  refresh();
}

void display_dir() {
  struct dirent *dir;
  DIR *d = opendir(song_dir);

  mvprintw(row++, 0, "Files:");

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      char *name = dir->d_name;

      if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
        continue;
      }

      mvprintw(row++, 0, "%s\n", name);
    }
  }

  closedir(d);
}

void player() {
  if (pause != 0) {
    return;
  }

  read = fread(buffer, 1, buf_size, fp);

  mvprintw(row++, 0, "Playing: %lu bytes\n", read);

  if (read <= 0) {
    return;
  }

  ao_play(device, buffer, read);
}

void select_file() {
  int index = 0;
  int ch;

  mvprintw(row++, 0, "Enter filename: %s", filename);
  refresh();

  while (1) {
    ch = getch();

    if (ch == ERR)
      continue;

    if (ch == '\n') {
      filename[index] = '\0';

      char full_path[512] = {0};
      snprintf(full_path, sizeof(full_path), "%s%s", song_dir, filename);

      if (fp)
        fclose(fp);

      fp = fopen(full_path, "rb");

      if (fp) {
        mvprintw(row++, 0, "File loaded: %s", filename);
      } else {
        mvprintw(row++, 0, "File not found: %s", filename);
      }

      pause = 1;
      return;
    }

    if ((ch == KEY_BACKSPACE || ch == 127 || ch == 8) && index > 0) {
      index--;
      filename[index] = '\0';
    } else if (isprint(ch) && index < sizeof(filename) - 1) {
      filename[index++] = ch;
      filename[index] = '\0';
    }

    move(row - 1, 0);
    clrtoeol();

    mvprintw(row - 1, 0, "Enter filename: %s", filename);
    refresh();
  }
}

void read_command() {
  refresh();
  key = getch();

  if (key == ERR) {
    return;
  }

  switch (key) {
  case KEY_F(1):
    display_dir();
    break;
  case KEY_F(2):
    select_file();
    break;
  case KEY_F(3):
    pause = 0;
    clear();
    row = 0;
    move(row, 0);
    display_player();
    break;
  case KEY_F(4):
    pause = 1;
    clear();
    row = 0;
    move(row, 0);
    display_player();
    break;
  case KEY_F(5):
    pause = 1;
    rewind(fp);
    clear();
    row = 0;
    move(row, 0);
    display_player();
    break;
  case KEY_ESC:
    end = 1;
    break;
  default:
    break;
  }
}

void lesson_4() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  scrollok(stdscr, TRUE);
  idlok(stdscr, TRUE);

  display_player();

  int default_driver;
  ao_initialize();
  default_driver = ao_default_driver_id();

  memset(&format, 0, sizeof(format));
  format.bits = 16;
  format.channels = 2;
  format.rate = 44100;
  format.byte_format = AO_FMT_LITTLE;

  buf_size = format.bits / 8 * format.channels * format.rate;
  buffer = malloc(buf_size);

  device = ao_open_live(default_driver, &format, NULL);
  if (!device) {
    printf("Error opening device.\n");
    mvprintw(row++, 0, "Error opening device.");
    end = 1;
  }

  while (!end) {
    read_command();
    player();

    nanosleep(&ts, NULL);
  }

  endwin();

  fclose(fp);
  ao_close(device);
  ao_shutdown();
}

// Exercise 5.1
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

    printf("\033[%dm%03d\033[0m\n", color, i);
  }
}

// Exercise 5.2
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

void ex_5_2() {
  char *title = "Array 001";

  char *name_title = "Name";
  char *name = "David Tsofin";

  char *height_title = "Height";
  char *height = "175cm";

  char *weight_title = "Weight";
  char *weight = "85kg";

  char *phone_title = "Phone";
  char *phone = "0950 710 314";

  int title_width = max_str(
      (char *[]){name_title, height_title, phone_title, weight_title}, 4);

  int value_width = max_str((char *[]){name, height, phone, weight}, 4);

  printf("+-%-*s-+-%-*s-+\n", title_width, gen_str('-', title_width),
         value_width, gen_str('-', value_width));

  printf("| %-*s | %-*s |\n", title_width, name_title, value_width, name);
  printf("| %-*s | %-*s |\n", title_width, height_title, value_width, height);
  printf("| %-*s | %-*s |\n", title_width, weight_title, value_width, weight);
  printf("| %-*s | %-*s |\n", title_width, phone_title, value_width, phone);

  printf("+-%-*s-+-%-*s-+\n", title_width, gen_str('-', title_width),
         value_width, gen_str('-', value_width));
}

// Exercise 6
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

  mvprintw(row++, 0, "WELCOME TO THE REACTION TEST");

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
      mvprintw(row++, 0, "Instructions...");
      break;
    case KEY_F(2):
      mvprintw(row++, 0, "Test started...");
      start_time = clock();
      break;
    case KEY_ESC:
      end = 1;
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

        mvprintw(row++, 0, "Key %c pressed: %.2f seconds", (char)key,
                 (float)(clock() - start_time) / CLOCKS_PER_SEC);
      } else {
        prev_key = 0;
      }

      break;
    }
  }
  endwin();
}

// Main function
int main() {
  printf("Running Exercise 1.1...\n");
  ex_1_1();

  printf("\nRunning Exercise 1.2...\n");
  ex_1_2();

  printf("\nRunning Exercise 1.3...\n");
  ex_1_3();

  printf("\nRunning Exercise 4...\n");
  lesson_4();

  printf("\nRunning Exercise 5.1...\n");
  ex_5_1();

  printf("\nRunning Exercise 5.2...\n");
  ex_5_2();

  printf("\nRunning Exercise 6...\n");
  lesson_6();

  return 0;
}