#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"      // Makra, vahy a bias hodnoty -- NEMENIT !!!
#include "functions.h" // Swish funkcia a pomocne funkcie -- NEMENIT !!!

const unsigned int img_height = 28, img_width = 28;
const int image_size = img_height * img_width;

const int neurons_count = 10;

int findmax(const double input[], int length) {
  int index = 0;
  for (int i = 1; i < length; ++i) {
    if (input[i] > input[index]) {
      index = i;
    }
  }

  return index;
}

void softmax(const double input[], double output[], int length) {
  double max = input[0];
  for (int i = 1; i < length; ++i) {
    if (input[i] > max) {
      max = input[i];
    }
  }

  double sum = 0.0;
  for (int i = 0; i < length; ++i) {
    output[i] = exp(input[i] - max);
    sum += output[i];
  }

  for (int i = 0; i < length; ++i) {
    output[i] /= sum;
  }
}

void load_int(int *input, const unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    scanf("%d", &input[i]);
  }
}

void load_double(double *input, const unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    scanf("%lf", &input[i]);
  }
}

void mode_1(void) {
  double img[image_size];

  load_image(img, image_size);
  print_image(img, img_width, img_height);
}

void mode_2(void) {
  unsigned int index, row, column;
  scanf("%u", &index);
  scanf("%u", &row);
  scanf("%u", &column);

  if (index > 9) {
    return;
  }

  printf("%.2lf", weights[(index * 784) + row * 28 + column]);
}

void mode_3(void) {
  double img[image_size];

  load_image(img, image_size);

  for (int index = 0; index < neurons_count; ++index) {
    double sum = bias[index];

    for (int i = 0; i < image_size; ++i) {
      sum += img[i] * weights[index * image_size + i];
    }

    printf("%8d%8.2f", index, sum);
    if (index < neurons_count - 1) {
      printf("\n");
    }
  }
}

void mode_4(void) {
  double input[neurons_count];
  double output[neurons_count];

  load_double(input, neurons_count);

  softmax(input, output, neurons_count);

  for (int i = 0; i < neurons_count; ++i) {
    printf("%.2f", output[i]);
    if (i < neurons_count - 1) {
      printf(" ");
    }
  }
}

void mode_5(void) {
  double input[neurons_count];
  load_double(input, neurons_count);

  printf("%d", findmax(input, neurons_count));
}

void mode_6(void) {
  double img[image_size];
  load_image(img, image_size);

  double hidden[10];

  for (int index = 0; index < 10; ++index) {
    double sum = bias[index];

    for (int i = 0; i < image_size; ++i) {
      sum += img[i] * weights[index * 784 + i];
    }

    hidden[index] = swish(sum);
  }

  double softed[10];
  softmax(hidden, softed, 10);

  printf("%d", findmax(softed, 10));
}

void mode_7(void) {
  int count;
  scanf("%d", &count);

  int labels[count];
  for (int i = 0; i < count; ++i) {
    if (scanf("%d", &labels[i]) != 1)
      return;
  }

  double images[count][image_size];
  for (int i = 0; i < count; ++i) {
    load_image(images[i], image_size);
  }

  int correct_count = 0;

  int results[count][3];

  for (int i = 0; i < count; ++i) {
    double hidden[neurons_count];

    for (int neuron = 0; neuron < neurons_count; ++neuron) {
      double sum = bias[neuron];
      for (int j = 0; j < image_size; ++j) {
        sum += images[i][j] * weights[neuron * image_size + j];
      }

      hidden[neuron] = swish(sum);
    }

    double softed[10];
    softmax(hidden, softed, 10);

    int prediction = findmax(softed, 10);

    if (prediction == labels[i]) {
      correct_count++;
    }

    results[i][0] = i;
    results[i][1] = labels[i];
    results[i][2] = prediction;
  }

  printf("%.2f ", (double)correct_count / count * 100.0);

  for (int i = 0; i < count; ++i) {
    printf("%d-%d-%d", results[i][0], results[i][1], results[i][2]);
    if (i < count - 1) {
      printf(" ");
    }
  }
}

int main(void) {
  unsigned int mode;

  if (scanf("%d", &mode) != 1) {
    return 1;
  }

  switch (mode) {
  case 1:
    mode_1();
    break;
  case 2:
    mode_2();
    break;
  case 3:
    mode_3();
    break;
  case 4:
    mode_4();
    break;
  case 5:
    mode_5();
    break;
  case 6:
    mode_6();
    break;
  case 7:
    mode_7();
    break;
  default:
    return 1;
  }

  return 0;
}
