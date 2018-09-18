#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  printf("enter:\n");
  int array_1[] = {1, 3, 4, 1, 4, 0};
  int array_2[] = {0};
  int array_3[] = {-1, -3, -4, -5, -6, -9};
  int array_4[] = {0, 0, 0, 0, 0, 0};
  int array_5[] = {-1, 3, 4, 5, 6, 7};
  int array_6[] = {3, 3, 4, 4, 4};
  if (maxSeq(array_1, 6) != 3)
    return EXIT_FAILURE;
  if (maxSeq(array_2, 0) != 0)
    return EXIT_FAILURE;
  if (maxSeq(array_3, 6) != 1)
    return EXIT_FAILURE;
  if (maxSeq(array_4, 6) != 1)
    return EXIT_FAILURE;
  if (maxSeq(array_5, 6) != 6)
    return EXIT_FAILURE;
  if (maxSeq(array_6, 5) != 2)
    return EXIT_FAILURE;
  printf("successful!\n");
  return EXIT_SUCCESS;
}
