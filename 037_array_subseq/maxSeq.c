#include <stdio.h>

size_t max(size_t a, size_t b) {
  if (a >= b)
    return a;
  else
    return b;
}

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  else {
    int p = 0, q = 1;
    size_t lenth = 1, max_lenth = 1;
    while (q < n) {
      if (array[q] > array[p]) {
        lenth++;
        p++;
        q++;
        max_lenth = max(max_lenth, lenth);
      }
      else {
        max_lenth = max(max_lenth, lenth);
        lenth = 1;
        p++;
        q++;
      }
    }
    return max_lenth;
  }
}
