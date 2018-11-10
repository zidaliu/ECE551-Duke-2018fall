#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

void load(const char * path, unordered_map<string, string> & map) {
  struct stat st;
  string address;
  lstat(path, &st);

  if (S_ISREG(st.st_mode)) {
    string value(path);
    ifstream f(path);
    ostringstream buff;
    char ch;
    while (buff && f.get(ch)) {
      buff.put(ch);
    }
    string key = buff.str();

    if (map.find(key) == map.end()) {
      map.insert(make_pair(key, value));
    }
    else {
      unordered_map<string, string>::iterator itr;
      for (itr = map.begin(); itr != map.end(); itr++) {
        if (itr->first == key) {
          cout << "#Removing " << path << " (duplicate of " << itr->second << ").\n\nrm " << path
               << "\n\n";
        }
      }
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
      if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
        continue;
      stringstream ss;
      ss << path << '/' << filename->d_name;
      load(ss.str().c_str(), map);
    }
    closedir(dir);
  }
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    cout << "I need at least one argument, sorry.\n";
    return 0;
  }
  cout << "#!/bin/bash\n";
  unordered_map<string, string> umap;
  for (int i = 1; i < argc; i++) {
    load(argv[i], umap);
  }
  return EXIT_SUCCESS;
}
