#include <stdio.h>
#include <stdlib.h>

void printMatrix(char matrix[10][10]) {
  int i, j;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      printf("%c", matrix[10 - 1 - j][i]);
    }
    printf("\n");
  }
}

void read_line(char matrix_line[10], FILE * f) {
  int i = 0;
  for (;;) {
    int ch = fgetc(f);
    switch (ch) {
      case 10:
        if (i == 10) {
          return;
        }
        else {
          fprintf(stderr, "New line comes too quick");
          exit(EXIT_FAILURE);
        }
        break;

      case EOF:
        fprintf(stderr, "ECF too quick, line is too short\n");
        exit(EXIT_FAILURE);
        break;

      default:
        if (i < 10) {
          matrix_line[i++] = (char)ch;
        }
        else {
          fprintf(stderr, "line too long");
          exit(EXIT_FAILURE);
        }
        break;
    }
  }
}

int main(int argc, char ** argv) {
  char matrix[10][10];
  FILE * f;
  int ch;
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix input\n");
    exit(EXIT_FAILURE);
  }
  if ((f = fopen(argv[1], "r")) == 0) {
    fprintf(stderr, "Could not open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 10; i++) {
    read_line(*(matrix + i), f);
  }
  if ((ch = fgetc(f)) != EOF) {
    fprintf(stderr, "Too much line\n");
    exit(EXIT_FAILURE);
  }
  fclose(f);
  printMatrix(matrix);
  return 0;
}
