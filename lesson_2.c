#include <math.h>
#include <stdio.h>
#include <string.h>

double f_1(double x) {
  if (x < 0) {
    return 0.00;
  }

  return 1.00;
}

double f_2(double x) {
  if (x > 0) {
    return x;
  }

  return 0.00;
}

double f_3(double x) {
  const int b = 2;
  return (x + sqrt(((x * x) + b))) / 2;
}

double f_4(double x) { return exp(-(x * x)); }

double f_5(double x) { return tanh(x); }

double f_6(double x) {
  const float b = 0.5;
  return x / (1 + exp(-b * x));
}

char *f_name(int f) {
  switch (f) {
  case 1:
    return "f_1";
  case 2:
    return "f_3";
  case 3:
    return "f_3";
  case 4:
    return "f_4";
  case 5:
    return "f_5";
  case 6:
    return "f_6";
  default:
    return "";
  }
}

int main() {
  char input[1024];
  fgets(input, sizeof(input), stdin);

  char *token = strtok(input, " ");

  double x_start, x_stop, step;

  if (!token || !sscanf(token, "%lf", &x_start)) {
    printf("E1");
    return 0;
  }
  token = strtok(NULL, " ");

  if (!token || !sscanf(token, "%lf", &x_stop)) {
    printf("E1");
    return 0;
  }
  token = strtok(NULL, " ");

  if (!token || !sscanf(token, "%lf", &step)) {
    printf("E1");
    return 0;
  }
  token = strtok(NULL, " ");

  int precision, width;

  if (!token || !sscanf(token, "%d", &precision)) {
    printf("E1");
    return 0;
  }
  token = strtok(NULL, " ");

  if (!token || !sscanf(token, "%d", &width)) {
    printf("E1");
    return 0;
  };
  token = strtok(NULL, " ");

  char symbol[1];

  int functions[100] = {};
  int functions_count = 0;

  while (token) {
    int func;
    if (sscanf(token, "%d", &func)) {
      functions[functions_count] = func;
      functions_count++;

      token = strtok(NULL, " ");

      continue;
    }

    break;
  }

  if (x_start >= x_stop) {
    printf("E2");
    return 0;
  }

  if (functions_count) {
    int exist_fun = 0;
    for (int f = 0; f < functions_count; f++) {
      if (functions[f]) {
        exist_fun++;
      }
    }

    if (!exist_fun) {
      return 0;
    }

    printf("%*s", width, "x");

    for (double x = x_start; x <= x_stop; x += step) {
      printf("%*.*f", width, precision, x);
    }

    printf("\n");

    for (int f = 0; f < functions_count; f++) {
      if (!(functions[f] < 7 && functions[f] > 0)) {
        continue;
      }

      printf("%*d", width, functions[f]);

      for (double x = x_start; x <= x_stop; x += step) {
        switch (functions[f]) {
        case 1:
          printf("%*.*f", width, precision, f_1(x));
          break;
        case 2:
          printf("%*.*f", width, precision, f_2(x));
          break;
        case 3:
          printf("%*.*f", width, precision, f_3(x));
          break;
        case 4:
          printf("%*.*f", width, precision, f_4(x));
          break;
        case 5:
          printf("%*.*f", width, precision, f_5(x));
          break;
        case 6:
          printf("%*.*f", width, precision, f_6(x));
          break;
        default:
          continue;
        }
      }

      printf("\n");
    }
  } else {
    printf("%*s", width, "x");
    printf("%*d", width, 1);
    printf("%*d", width, 2);
    printf("%*d", width, 3);
    printf("%*d", width, 4);
    printf("%*d", width, 5);
    printf("%*d", width, 6);

    printf("\n");

    for (double x = x_start; x <= x_stop; x += step) {
      printf("%*.*lf", width, precision, x);
      printf("%*.*f", width, precision, f_1(x));
      printf("%*.*f", width, precision, f_2(x));
      printf("%*.*f", width, precision, f_3(x));
      printf("%*.*f", width, precision, f_4(x));
      printf("%*.*f", width, precision, f_5(x));
      printf("%*.*f", width, precision, f_6(x));
      printf("\n");
    }
  }

  return 0;
}
