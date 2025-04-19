#include <ao/ao.h>
#include <ctype.h>
#include <dirent.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  mvprintw(row++, 0, "|                                             |");
  mvprintw(row++, 0, "|         WELCOME TO THE STRANGE PLAYER       |");
  mvprintw(row++, 0, "|                                             |");
  mvprintw(row++, 0, "+---------------------------------------------+");
  mvprintw(row++, 0, "|  Test your reflexes with this simple game!  |");
  mvprintw(row++, 0, "|  Press F1 list songs.                       |");
  mvprintw(row++, 0, "|  Press F2 to select song.                   |");
  mvprintw(row++, 0, "|  Press F3 to play.                          |");
  mvprintw(row++, 0, "|  Press F4 to pause.                         |");
  mvprintw(row++, 0, "|  Press F5 to stop.                          |");
  mvprintw(row++, 0, "|  Press ESC                                  |");
  mvprintw(row++, 0, "+---------------------------------------------+");
  mvprintw(row++, 0, "select song: %s", filename);

  switch (pause) {
  case 0:
    mvprintw(row++, 0, "state: playing");
    break;
  case 1:
    mvprintw(row++, 0, "state: paused");
    break;
  case 2:
    mvprintw(row++, 0, "state: stopped");
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

  mvprintw(row++, 0, "playing: %lu\n", (float)read);

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
  int sample;
  float freq = 440.0;
  int i;

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

int main() {
  lesson_4();

  return 0;
}