unsigned power(unsigned x, unsigned y) {
  if (0 == y)
    return 1;
  else if (1 == y)
    return x;
  else
    return x * power(x, y - 1);
}
