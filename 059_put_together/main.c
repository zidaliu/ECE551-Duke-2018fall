#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f;
  char * curr = NULL;
  size_t sz;
  ssize_t byte;
  f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Not open the file");
  }
  counts_t * counts = createCounts();
  while ((byte = getline(&curr, &sz, f)) >= 0) {
    if (byte > 0 && curr[byte - 1] == '\n') {
      curr[byte - 1] = '\0';
    }
    addCount(counts, lookupValue(kvPairs, curr));
  }
  free(curr);
  fclose(f);

  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 1) {
    fprintf(stderr, "need at least one argument\n");
    exit(EXIT_FAILURE);
  }

  kvarray_t * kv;
  counts_t * c;
  char * outName;
  kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      perror("can't open file");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    free(c);
  }

  //free the memory for kv
  free(kv);
  return EXIT_SUCCESS;
}
