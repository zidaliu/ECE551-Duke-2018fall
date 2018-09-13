unsigned power(unsigned x, unsigned n) {
  if (0 == n)
    return 1;
  else if (1 == n)
    return x;
  else
    return x * power(x, n - 1);
}
