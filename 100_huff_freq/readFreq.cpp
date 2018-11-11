#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
using namespace std;
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  ifstream f(fname);
  char ch;
  uint64_t * freq = new uint64_t[257]();
  while (f.get(ch)) {
    freq[(unsigned char)ch]++;
  }
  freq[256] = 1;
  return freq;
}
