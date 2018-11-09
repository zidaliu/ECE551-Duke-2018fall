#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#define HASH_INISIZ 64

class Hashset
{
 private:
  struct Slot {
    const char * path;
    bool flag = false;
  };
  Slot * hvec;
  size_t hsiz;
  size_t hash(istream & f) {
    size_t h = 6549;
    while (!f.eof()) {
      h = h * 1558 + ((unsigned char)f.get() ^ 233);
    }
    return h;
  }
  bool equal(istream & f1, istream & f2) {
    while (!f1.eof() && !f2.eof()) {
      if (f1.get() != f2.get()) {
        return false;
      }
    }
    return f1.eof() && f2.eof();
  }

 public:
  Hashset() : hvec(new Slot[HASH_INISIZ]()), hsiz(HASH_INISIZ) {}
  void addFile(const char * path) {
    ifstream f(path);
    size_t h = hash(f);
    hvec[h % hsiz].path = path;
    hvec[h % hsiz].flag = true;
  }
  const char * findDup(const char * path) {
    ifstream f(path);
    size_t h = hash(f);
    if (hvec[h % hsiz].flag) {
      return hvec[h % hsiz].path;  //找到了
    }
    return "a";  //没找到
  }

  ~Hashset() { delete[] hvec; }
};

void load(const char * path, Hashset & set) {
  struct stat st;
  const char * address;
  lstat(path, &st);

  if (S_ISREG(st.st_mode)) {
    address = set.findDup(path);
    if (strcmp(address, "a") != 0) {
      cout << "#Removing " << path << " (duplicate of " << address << ").\n\nrm " << path << "\n\n";
    }
    else {
      set.addFile(path);
    }
  }
  else if (S_ISDIR(st.st_mode)) {
    /*get all the file in the dir*/
    struct dirent * filename;  // return value for readdir()
    DIR * dir;
    dir = opendir(path);
    if (NULL == dir) {
      cout << "Can not open dir " << path << endl;
      return;
    }
    /* read all the files in the dir ~ */
    while ((filename = readdir(dir)) != NULL) {
      // get rid of "." and ".
      if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
        continue;
      stringstream ss;
      ss << path << '/' << filename->d_name;
      load(ss.str().c_str(), set);
    }
    free(dir);
  }
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    cout << "I need at least one argument, sorry.\n";
    return 0;
  }
  cout << "#!/bin/bash\n";
  Hashset set;
  for (int i = 1; i < argc; i++) {
    load(argv[i], set);
  }
  return 0;
}
