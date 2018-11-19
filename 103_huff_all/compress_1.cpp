#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"
using namespace std;

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  ifstream f(inFile);
  char ch;
  //You need to read the input file, lookup the characters in the map,
  map<unsigned, BitString>::const_iterator iter;
  while (f.get(ch)) {
    iter = theMap.find((unsigned char)ch);
    bfw.writeBitString(iter->second);
  }
  //and write the proper bit string with the BitFileWriter
  iter = theMap.find(256);
  bfw.writeBitString(iter->second);
  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  const char * input = argv[1];
  const char * output = argv[2];
  uint64_t * fre = readFrequencies(input);
  Node * tree = buildTree(fre);
  delete[] fre;
  BitString b;
  map<unsigned, BitString> theMap;
  tree->buildMap(b, theMap);
  delete tree;
  writeCompressedOutput(input, output, theMap);
  return EXIT_SUCCESS;
}
