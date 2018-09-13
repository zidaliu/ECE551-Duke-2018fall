#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned temp = power(x, y);
  if (expected_ans != temp) {
    printf("Expected_ans is %d, However your ans is %d\n", expected_ans, temp);
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  run_check(-2, 2, 4);
  run_check(-3, 3, -27);
  run_check(0, 0, 1);
  run_check(0.1, 2, 0.01);
  return 0;
}
