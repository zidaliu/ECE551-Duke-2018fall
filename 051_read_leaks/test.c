#include <stdio.h>
#include <stdlib.h>

int f(int n) {
  int * p = malloc(2 * sizeof(*p));
  p[0] = n;
  p[1] = n + 2;
  int ans = p[0] * p[1];
  free(p);
  return ans;
}

int main(void) {
  int * p = malloc(4 * sizeof(*p));
  int * q = p;
  int ** r = &q;
  p[0] = f(1);
  *r = NULL;
  free(p);
  q = malloc(2 * sizeof(*q));
  p = q;
<<<<<<< HEAD
  free(p);
  q = NULL;
=======
  q = NULL;
  free(p);
>>>>>>> 5e02df56dad2eb125a1a66ecd86db9baf7996374
  return EXIT_SUCCESS;
}
