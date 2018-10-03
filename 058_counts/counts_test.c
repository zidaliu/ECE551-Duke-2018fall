#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 12
int main(void) {
  char * testData[NUM_TESTS] = {"apple",
                                "banana",
                                NULL,
                                "apple",
                                "forg",
                                "sword",
                                "bear",
                                NULL,
                                "frog",
                                "apple",
                                "zebra",
                                "knight"};
  counts_t * testCounts = createCounts();
  for (int i = 0; i < NUM_TESTS; i++) {
    addCount(testCounts, testData[i]);
  }
  /*  addCount(testCounts, testData[1]);
  addCount(testCounts, testData[2]);
  addCount(testCounts, testData[3]);
  addCount(testCounts, testData[4]);
  */
  printCounts(testCounts, stdout);
  freeCounts(testCounts);
  return EXIT_SUCCESS;
}
