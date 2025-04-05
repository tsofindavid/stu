#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAX 1000
#define N 100

#define CMD_IN 1
#define CMD_STR_IN "in"

#define CMD_OUT 2
#define CMD_STR_OUT "out"

#define CMD_OP 3
#define CMD_STR_OP "op"

#define CMD_RANGE 4
#define CMD_STR_RANGE "range"

#define CMD_MEM 5
#define CMD_STR_MEM "mem"

#define CMD_MOVE 6
#define CMD_STR_MOVE "move"

#define CMD_SP 7
#define CMD_STR_SP "sp"

#define CMD_EP 8
#define CMD_STR_EP "ep"

#define CMD_START 9
#define CMD_STR_START "start"

#define CMD_END 10
#define CMD_STR_END "end"

#define CMD_FIRST 11
#define CMD_STR_FIRST "first"

#define CMD_LAST 12
#define CMD_STR_LAST "last"

#define CMD_PREV 13
#define CMD_STR_PREV "prev"

#define CMD_NEXT 14
#define CMD_STR_NEXT "next"

#define CMD_DEL 15
#define CMD_STR_DEL "del"

#define CMD_CROP 16
#define CMD_STR_CROP "crop"

#define CMD_COPY 17
#define CMD_STR_COPY "copy"

#define CMD_INSERT 18
#define CMD_STR_INSERT "insert"

#define CMD_REPLACE 19
#define CMD_STR_REPLACE "replace"

#define CMD_QUIT 20
#define CMD_STR_QUIT "quit"

char op[N + 1] = {0};
char mem[N + 1] = {0};
int sp, ep = 0;

int get_command_code(const char *cmd) {
  if (strcmp(cmd, CMD_STR_IN) == 0)
    return CMD_IN;
  if (strcmp(cmd, CMD_STR_OUT) == 0)
    return CMD_OUT;
  if (strcmp(cmd, CMD_STR_OP) == 0)
    return CMD_OP;
  if (strcmp(cmd, CMD_STR_RANGE) == 0)
    return CMD_RANGE;
  if (strcmp(cmd, CMD_STR_MEM) == 0)
    return CMD_MEM;
  if (strcmp(cmd, CMD_STR_MOVE) == 0)
    return CMD_MOVE;
  if (strcmp(cmd, CMD_STR_SP) == 0)
    return CMD_SP;
  if (strcmp(cmd, CMD_STR_EP) == 0)
    return CMD_EP;
  if (strcmp(cmd, CMD_STR_START) == 0)
    return CMD_START;
  if (strcmp(cmd, CMD_STR_END) == 0)
    return CMD_END;
  if (strcmp(cmd, CMD_STR_FIRST) == 0)
    return CMD_FIRST;
  if (strcmp(cmd, CMD_STR_LAST) == 0)
    return CMD_LAST;
  if (strcmp(cmd, CMD_STR_PREV) == 0)
    return CMD_PREV;
  if (strcmp(cmd, CMD_STR_NEXT) == 0)
    return CMD_NEXT;
  if (strcmp(cmd, CMD_STR_DEL) == 0)
    return CMD_DEL;
  if (strcmp(cmd, CMD_STR_CROP) == 0)
    return CMD_CROP;
  if (strcmp(cmd, CMD_STR_COPY) == 0)
    return CMD_COPY;
  if (strcmp(cmd, CMD_STR_INSERT) == 0)
    return CMD_INSERT;
  if (strcmp(cmd, CMD_STR_REPLACE) == 0)
    return CMD_REPLACE;
  if (strcmp(cmd, CMD_STR_QUIT) == 0)
    return CMD_QUIT;

  return -1;
}

int get_command_length(int cmd_code) {
  switch (cmd_code) {
  case CMD_IN:
    return strlen(CMD_STR_IN);
  case CMD_OUT:
    return strlen(CMD_STR_OUT);
  case CMD_OP:
    return strlen(CMD_STR_OP);
  case CMD_RANGE:
    return strlen(CMD_STR_RANGE);
  case CMD_MEM:
    return strlen(CMD_STR_MEM);
  case CMD_MOVE:
    return strlen(CMD_STR_MOVE);
  case CMD_SP:
    return strlen(CMD_STR_SP);
  case CMD_EP:
    return strlen(CMD_STR_EP);
  case CMD_START:
    return strlen(CMD_STR_START);
  case CMD_END:
    return strlen(CMD_STR_END);
  case CMD_FIRST:
    return strlen(CMD_STR_FIRST);
  case CMD_LAST:
    return strlen(CMD_STR_LAST);
  case CMD_PREV:
    return strlen(CMD_STR_PREV);
  case CMD_NEXT:
    return strlen(CMD_STR_NEXT);
  case CMD_DEL:
    return strlen(CMD_STR_DEL);
  case CMD_CROP:
    return strlen(CMD_STR_CROP);
  case CMD_COPY:
    return strlen(CMD_STR_COPY);
  case CMD_INSERT:
    return strlen(CMD_STR_INSERT);
  case CMD_REPLACE:
    return strlen(CMD_STR_REPLACE);
  case CMD_QUIT:
    return strlen(CMD_STR_QUIT);
  default:
    return -1;
  }
}

char *readline() {
  static char buffer[MMAX + 1] = {0};
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}

char *rotate_line(const char *line, int skip) {
  static char result[MMAX + 1];
  strncpy(result, line + skip, strlen(line) - skip + 1);
  return result;
}

int cmd_out_op() {
  printf("%s\n", op);
  return 0;
}
int cmd_out_range() {
  if (sp > ep) {
    printf("ERR_POSITION");
    return 1;
  }

  int range_size = ep - sp;
  char range[range_size];

  for (int i = sp; i < ep; i++) {
    range[i - sp] = op[i];
  }

  range[range_size] = '\0';

  printf("%s\n", range);
  return 0;
}

int scan_command(char *line) {
  char cmd[10];

  if (sscanf(line, "%s", cmd) != 1) {
    return -1;
  };

  int cmd_code = get_command_code(cmd);

  return cmd_code;
}

int cmd_out_mem() {
  printf("%s\n", mem);
  return 0;
}

int cmd_move_sp(char *line) {
  sp = sp + atoi(line);

  if (sp < 0 || strlen(op) < sp) {
    printf("ERR_POSITION");
    return 1;
  }

  return 0;
}

int cmd_move_ep(char *line) {
  ep = ep + atoi(line);

  if (ep < 0 || strlen(op) < ep) {
    printf("ERR_POSITION");
    return 1;
  }

  return 0;
}

int cmd_out(char *line) {
  int cmd_out_code = scan_command(line);
  line = rotate_line(line, get_command_length(cmd_out_code) + 1);

  switch (cmd_out_code) {
  case CMD_OP:
    return cmd_out_op();
  case CMD_RANGE:
    return cmd_out_range();
  case CMD_MEM:
    return cmd_out_mem();
  default:
    return 1;
  }

  return 0;
}

int cmd_in(char *line) {
  if (strlen(line) > N + 1) {
    printf("ERR_OVERFLOW");
    return 1;
  }

  if (sscanf(line, "%[^\n]", op) != 1) {
    printf("ERR_INVALID_ARG");
    return 1;
  }

  sp = 0;
  ep = strlen(op);

  printf("sp: %d\n", sp);
  printf("ep: %d\n", ep);

  return 0;
}

int cmd_move(char *line) {
  int cmd_move_code = scan_command(line);
  line = rotate_line(line, get_command_length(cmd_move_code) + 1);

  switch (cmd_move_code) {
  case CMD_SP:
    return cmd_move_sp(line);
  case CMD_EP:
    return cmd_move_ep(line);
  default:
    return 1;
  }

  return 0;
}

int cmd_start(char *line) {
  int cmd_move_code = scan_command(line);
  line = rotate_line(line, get_command_length(cmd_move_code) + 1);

  switch (cmd_move_code) {
  case CMD_SP:
    return cmd_move_sp(line);
  case CMD_EP:
    return cmd_move_ep(line);
  default:
    return 1;
  }

  return 0;
}

int main() {
  int exit = 1;

  while (exit) {
    char *line = readline();

    int cmd_code = scan_command(line);
    line = rotate_line(line, get_command_length(cmd_code) + 1);

    switch (cmd_code) {
    case CMD_IN:
      if (cmd_in(line) == 1) {
        exit = 0;
      }
      break;
    case CMD_OUT:
      if (cmd_out(line) == 1) {
        exit = 0;
      }
      break;
    case CMD_MOVE:
      if (cmd_move(line) == 1) {
        exit = 0;
      }
      break;
    case CMD_SP:
      break;
    case CMD_EP:
      break;
    case CMD_START:
      break;
    case CMD_END:
      break;
    case CMD_FIRST:
      break;
    case CMD_LAST:
      break;
    case CMD_PREV:
      break;
    case CMD_NEXT:
      break;
    case CMD_DEL:
      break;
    case CMD_CROP:
      break;
    case CMD_COPY:
      break;
    case CMD_INSERT:
      break;
    case CMD_REPLACE:
      break;
    case CMD_QUIT:
      exit = 0;
      break;
    default:
      continue;
    }
  }

  return 0;
}