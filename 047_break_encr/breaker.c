#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int findMax(int * array, int n) {
  int temp = 0;
  int i;

  for (i = 0; i < n; i++) {
    if (array[i] > array[temp]) {
      temp = i;
    }
  }
  return temp;
}

int comKey(FILE * f) {
  int freq[26] = {0};
  int c;
  int max;

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      freq[tolower(c) - 'a']++;
    }
  }
  max = findMax(freq, 26);
  return max - 4;
}

int main(int argc, char ** argv) {
  FILE * f;
  int key;

  if (argc != 2) {
    fprintf(stderr, "usage %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "failed to open file %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  key = comKey(f);
  printf("%d\n", key);

  fclose(f);
  return 0;
}
