#include <ctype.h>
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

#define CMD_INFO 21
#define CMD_STR_INFO "info"

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
  if (strcmp(cmd, CMD_STR_INFO) == 0)
    return CMD_INFO;

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
  case CMD_INFO:
    return strlen(CMD_STR_INFO);
  default:
    return -1;
  }
}

int cmd_info() {
  printf("\n");
  printf("op: '%s'\n", op);
  printf("op_len: '%lu'\n", strlen(op));
  printf("mem: '%s'\n", mem);
  printf("sp: '%d'\n", sp);
  printf("ep: '%d'\n", ep);
  return 0;
}

char *readline() {
  static char buffer[MMAX + 1] = {0};
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}

char *rotate_line(const char *line, int skip) {
  int len = strlen(line);

  char *result = (char *)malloc(len - skip + 1);

  for (int i = 0; i < len - skip; i++) {
    result[i] = line[i + skip];
  }

  result[len - skip] = '\0';

  return result;
}

int cmd_out_op() {
  printf("%s\n", op);
  return 0;
}

int cmd_out_range() {
  if (sp > ep) {
    printf("ERR_POSITION\n");
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

int scan_command(char *line) {
  char cmd[100];

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
    printf("ERR_OUT_OF_RANGE\n");
    return 1;
  }

  return 0;
}

int cmd_move_ep(char *line) {
  ep = ep + atoi(line);

  if (ep < 0 || strlen(op) < ep) {
    printf("ERR_OUT_OF_RANGE\n");
    return 1;
  }

  return 0;
}

int cmd_start_sp() {
  sp = 0;
  return 0;
}

int cmd_start_ep() {
  ep = 0;
  return 0;
}

int cmd_end_sp() {
  sp = strlen(op);
  return 0;
}

int cmd_end_ep() {
  ep = strlen(op);
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
  if (strlen(line) > N) {
    printf("ERR_OVERFLOW\n");
    return 1;
  }

  if (sscanf(line, "%[^\n]", op) != 1) {
    printf("ERR_INVALID_ARG\n");
    return 1;
  }

  sp = 0;
  ep = strlen(op);

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

int cmd_end(char *line) {
  int cmd_move_code = scan_command(line);
  line = rotate_line(line, get_command_length(cmd_move_code) + 1);

  switch (cmd_move_code) {
  case CMD_SP:
    return cmd_end_sp();
  case CMD_EP:
    return cmd_end_ep();
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
    return cmd_start_sp();
  case CMD_EP:
    return cmd_start_ep();
  default:
    return 1;
  }

  return 0;
}

int cmd_first() {
  int len = strlen(op);

  sp = 0;
  ep = 0;

  for (int i = 0; i < len; i++) {
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

int cmd_last() {
  int len = strlen(op);

  sp = len;
  ep = len;

  for (int i = len; i >= 0; i--) {
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

int cmd_next_find() {
  int len = strlen(op);

  for (int i = sp; i < len; i++) {
    if (isalnum(op[i])) {
      sp = i;
      ep = len;

      for (int x = i; x < len; x++) {
        if (!isalnum(op[x])) {
          ep = x;
          return 0;
        }
      }

      return 0;
    }
  }

  sp = 0;
  ep = 0;

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

int cmd_del() {
  if (sp > ep) {
    printf("ERR_POSITION\n");
    return 1;
  }

  if (sp == ep) {
    return 0;
  }

  int len = strlen(op) - (ep - sp);
  char result[N + 1];

  int i = 0;
  int x = 0;

  while (i < len) {
    if (sp <= x && x < ep) {
      x++;
      continue;
    }

    result[i] = op[x];
    i++;
    x++;
  }

  result[len] = '\0';
  strcpy(op, result);

  ep = sp;

  return 0;
}

int cmd_crop() {
  if (sp > ep) {
    printf("ERR_POSITION\n");
    return 1;
  }

  int len = ep - sp;
  char result[N + 1];

  for (int i = 0; (i + sp) < ep; i++) {
    result[i] = op[i + sp];
  }

  result[len] = '\0';
  strcpy(op, result);

  sp = 0;
  ep = strlen(op);

  return 0;
}

int cmd_copy() {
  if (sp > ep) {
    printf("ERR_POSITION\n");
    return 1;
  }

  if (sp == ep) {
    return 0;
  }

  int len = ep - sp;
  char result[N + 1];

  for (int i = 0; (i + sp) < ep; i++) {
    result[i] = op[i + sp];
  }

  result[len] = '\0';
  strcpy(mem, result);
  return 0;
}

int cmd_insert_space(int n) {
  int op_len = strlen(op);

  if (op_len + n > N) {
    printf("ERR_OVERFLOW\n");
    return 1;
  }

  char result[N + 1];

  int shift = 0;
  for (int i = 0; i < op_len + 1; i++) {
    if (i == sp) {
      for (int d = 0; d < n; d++) {
        result[i + shift] = ' ';
        shift++;
      }
    }

    result[i + shift] = op[i];
  }

  //   int i = 0;
  //   int x = 0;
  //   while (i < op_len) {
  //     printf("i: %d, c: %c\n", i, op[i]);

  //     result[x] = op[i];
  //     i++;
  //     x++;

  //     if (i == sp) {
  //       for (int d = 0; d < n; d++) {
  //         printf("x: %d, c: %c\n", x, '*');
  //         result[x] = '*';
  //         x++;
  //       }
  //     }
  //   }

  //   printf("i: %d, x: %d, (op_len + n): %d\n", i, x, op_len + n);

  result[op_len + n] = '\0';
  strcpy(op, result);

  return 0;
}

int cmd_insert_mem() {
  int op_len = strlen(op);
  int mem_len = strlen(mem);

  if (op_len + mem_len > N) {
    printf("ERR_OVERFLOW\n");
    return 1;
  }

  char result[N + 1];

  int i = 0;
  int x = 0;
  while (i < op_len) {
    if (x == sp) {
      for (int d = 0; d < mem_len; d++) {
        result[x] = mem[d];
        x++;
      }
    }

    result[x] = op[i];
    i++;
    x++;
  }

  result[op_len + mem_len] = '\0';
  strcpy(op, result);

  return 0;
}

int cmd_insert(char *line) {
  int n;
  if (sscanf(line, "%d", &n) == 1) {
    return cmd_insert_space(n);
  }

  int cmd_out_code = scan_command(line);
  line = rotate_line(line, get_command_length(cmd_out_code) + 1);

  switch (cmd_out_code) {
  case CMD_MEM:
    return cmd_insert_mem();
  default:
    return 1;
  }

  return 0;
}

int cmd_replace() {
  if (sp > ep) {
    printf("ERR_POSITION\n");
    return 1;
  }

  if (sp == ep) {
    return 0;
  }

  if (strlen(mem) == 0) {
    return 0;
  }

  for (int i = 0; i < (ep - sp); i++) {
    if (mem[i]) {
      op[sp + i] = mem[i];
    }
  }

  return 0;
}

int main() {
  int exit = 1;

  while (exit) {
    // printf("op: %s\n", op);
    // printf("sp: %d\n", sp);
    // printf("ep: %d\n", ep);

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
    case CMD_START:
      if (cmd_start(line) == 1) {
        exit = 0;
      }
      break;
    case CMD_END:
      if (cmd_end(line) == 1) {
        exit = 0;
      }
      break;
    case CMD_FIRST:
      if (cmd_first() == 1) {
        exit = 0;
      }
      break;
    case CMD_LAST:
      if (cmd_last() == 1) {
        exit = 0;
      }
      break;
    case CMD_PREV:
      if (cmd_prev() == 1) {
        exit = 0;
      }
      break;
    case CMD_NEXT:
      if (cmd_next() == 1) {
        exit = 0;
      }
      break;
      break;
    case CMD_DEL:
      if (cmd_del() == 1) {
        exit = 0;
      }
      break;
    case CMD_CROP:
      if (cmd_crop() == 1) {
        exit = 0;
      }
      break;
    case CMD_COPY:
      if (cmd_copy() == 1) {
        exit = 0;
      }
      break;
    case CMD_INSERT:
      if (cmd_insert(line) == 1) {
        exit = 0;
      }
      break;
    case CMD_REPLACE:
      if (cmd_replace() == 1) {
        exit = 0;
      }
      break;
    case CMD_INFO:
      if (cmd_info() == 1) {
        exit = 0;
      }
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