#include <stdio.h>
#include <stdlib.h>  // This file is for Step 1.
// You should do
int seq1(int x) {
  int y;
  y = 4 * x - 3;
  return y;
}  //  Step 1 (A): write seq1

void printSeq1Range(int low, int high);

int main(void) {
  int a = 0;
  int b = 4;
  int c = 10;
  int d = -4;
  printf("seq1(%d)=%d\n", 0, seq1(a));
  printf("seq1(%d)=%d\n", 4, seq1(b));
  printf("seq1(%d)=%d\n", 10, seq1(c));
  printf("seq1(%d)=%d\n", -4, seq1(d));
  printf("printSeq1range(%d,%d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printSeq1range(%d,%d)\n", 3, 7);
  printSeq1Range(3, 7);
  printf("printSeq1range(%d,%d)\n", 7, 3);
  printSeq1Range(7, 3);
  printf("printSeq1range(%d,%d)\n", 0, 0);
  printSeq1Range(0, 0);
  return 0;
}  //  Step 1 (B): write main to test seq1

void printSeq1Range(int low, int high) {
  if (low < high) {
    for (int i = low; i < high; i++) {
      printf("%d", seq1(i));
      if (i != (high - 1)) {
        printf(", ");
      }
      else {
        printf("\n");
      }
    }
  }
  else {
    printf("\n");
  }
}

//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
