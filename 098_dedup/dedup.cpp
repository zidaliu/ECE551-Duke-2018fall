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
#define HASH_INISIZ 107

class Hashset
{
 public:
  class Linkedlist
  {
    class Node
    {
     public:
      string key;    //file contents
      string value;  //file path
      Node * next;
      Node * prev;

      Node(string k, string v, Node * next) : key(k), value(v), next(next), prev(NULL) {}
    };
    Node * head;
    Node * tail;
    size_t size;

   public:
    Linkedlist() : head(NULL), tail(NULL), size(0) {}
    void addFront(string data_k, string data_v) {
      tail = new Node(data_k, data_v, head);
      if (head == NULL) {
        head = tail;
      }
      else {
        tail->prev->next = tail;
      }
      size++;
    }
    /*compare within a bucket*/

    /*search in a bucket*/
    string search(string & content) {
      while (head != NULL) {
        if (head->key == content) {
          // cout << "pre :" << head->value << endl;
          return head->value;
        }
        head = head->next;
      }
      return "1";
    }
    ~Linkedlist() {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
    }
  };
  Linkedlist * hvec;
  size_t hsiz;
  size_t hash(istream & f) {
    size_t h = 6549;
    while (!f.eof()) {
      h = h * 1558 + ((unsigned char)f.get() ^ 233);
    }
    return h;
  }

  void addFile(string k, size_t v) {
    // cout << "index" << v % hsiz << " "
    //      << "add path: " << k << endl;
    string h_1 = to_string(v);  //h_1 is key is content
    hvec[v % hsiz].addFront(h_1, k);
  }

 public:
  Hashset() : hvec(new Linkedlist[HASH_INISIZ]()), hsiz(HASH_INISIZ) {}
  string findDup(const char * path) {
    ifstream f(path);
    size_t h = hash(f);
    string h_1 = to_string(h);
    string a(path);
    string b = "1";
    if (strcmp(hvec[h % hsiz].search(h_1).c_str(), b.c_str()) != 0) {
      // cout << "index" << h % hsiz << " "
      //      << "find pre: " << hvec[h % hsiz].search(h_1) << endl;
      return hvec[h % hsiz].search(h_1);  //find it
    }
    addFile(a, h);  // not find then puls
    return "a";
  }

  ~Hashset() { delete[] hvec; }
};

void load(const char * path, Hashset & set) {
  struct stat st;
  string address;
  lstat(path, &st);

  if (S_ISREG(st.st_mode)) {
    // cout << "The file path is " << path << endl;
    address = set.findDup(path);
    string a = "a";
    if (strcmp(address.c_str(), a.c_str()) != 0) {  //find it
      cout << "#Removing " << path << " (duplicate of " << address << ").\n\nrm " << path << "\n\n";
    }
    else {
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
      if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0 ||
          filename->d_type == DT_LNK) {
        continue;
      }
      stringstream ss;
      ss << path << '/' << filename->d_name;
      load(ss.str().c_str(), set);
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
  Hashset set;
  for (int i = 1; i < argc; i++) {
    load(argv[i], set);
  }
  return EXIT_SUCCESS;
}
