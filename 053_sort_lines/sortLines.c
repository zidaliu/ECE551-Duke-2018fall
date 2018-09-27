#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    char ** line = NULL;
    char * curr = NULL;
    size_t sz = 0;
    size_t i = 0;
    while (getline(&curr, &sz, stdin) != -1) {
      line = realloc(line, (i + 1) * sizeof(*line));
      line[i] = curr;
      curr = NULL;
      i++;
    }
    free(curr);
    sortData(line, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", line[j]);
      free(line[j]);
    }
    free(line);
  }

  else {
    FILE * f;
    //read files one by one
    for (int n = 1; n < argc; n++) {
      char ** line = NULL;
      char * curr = NULL;
      size_t sz = 0;
      size_t i = 0;
      f = fopen(argv[n], "r");
      //file doesn't exist
      if (f == NULL) {
        fprintf(stderr, "failed to open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
      }
      //file exists
      else {
        while (getline(&curr, &sz, f) != -1) {
          line = realloc(line, (i + 1) * sizeof(*line));
          line[i] = curr;
          curr = NULL;
          i++;
        }
        free(curr);
        sortData(line, i);
        // print sorted files
        for (size_t j = 0; j < i; j++) {
          printf("%s", line[j]);
          free(line[j]);
        }
        free(line);
      }
      if (fclose(f) != 0) {
        fprintf(stderr, "failed to close input\n");
        exit(EXIT_FAILURE);
      }
    }
  }

  return EXIT_SUCCESS;
}
