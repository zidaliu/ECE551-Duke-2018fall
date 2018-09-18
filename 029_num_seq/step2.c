#include <stdio.h>
#include <stdlib.h>
// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
int seq2(int x) {
  int y;
  y = x * x + 3 * x + 1;
  return y;
}

int sumSeq2(int x, int y);

//  Step 2 (B): write main to test seq2
int main(void) {
  printf("seq(%d) = %d\n", 1, seq2(1));
  printf("seq(%d) = %d\n", 5, seq2(5));
  printf("seq(%d) = %d\n", 13, seq2(13));
  printf("seq(%d) = %d\n", -4, seq2(-4));
  printf("sumSeq2(%d,%d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d,%d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d,%d) = %d\n", 9, 7, sumSeq2(9, 7));
}
//  Step 2 (C): write sumSeq2
int sumSeq2(int x, int y) {
  int sum = 0;
  if (x < y) {
    for (int i = x; i < y; i++) {
      sum += seq2(i);
    }
    return sum;
  }
  else {
    return 0;
  }
}
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
