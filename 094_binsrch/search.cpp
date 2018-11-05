#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  int begin = low;
  int end = high;
  while (begin + 1 != end) {
    int mid = begin + (begin - end) / 2;
    int ans = f->invoke(mid);
    if (ans == 0) {
      return mid;
    }
    else if (ans < 0) {
      begin = mid;
    }
    else {
      end = mid;
    }
    return begin;
  }
}
