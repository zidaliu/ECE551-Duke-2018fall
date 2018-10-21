#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void sortFile(istream & m) {
  string line;
  vector<string> array_line;
  while (getline(m, line)) {
    array_line.push_back(line);
  }
  sort(array_line.begin(), array_line.end());
  for (size_t i = 0; i < array_line.size(); i++) {
    cout << array_line[i] << endl;
  }
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    sortFile(cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      fstream f(argv[i]);
      if (!f) {
        cerr << "failed to open " << argv[i] << endl;
        exit(EXIT_FAILURE);
      }
      sortFile(f);
    }
  }
  return 0;
}
