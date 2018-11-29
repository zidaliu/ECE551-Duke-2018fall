#include "parse.h"

#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

int main() {
  while (1) {
    cout << "myShell$";
    char c;
    vector<char> a;
    string temp;
    while ((c = getchar()) != '\n') {
      if (c != EOF) {
        a.push_back(c);
      }
      else {
        cout << endl;
        exit(0);
      }
    }
    if (a.size() != 0) {
      a.push_back('\0');
      temp = a.data();
      string exit_line = "exit";
      if (temp == exit_line) {
        exit(0);
      }
    }
    else {
      continue;
    }
    string commond;
    string parameters;
    divided(temp, commond, parameters);
    if (parameters.length() > 0) {
      vector<string> final_parameter = getparmeter(parameters);
      for (size_t i = 0; i < final_parameter.size(); i++) {
        cout << final_parameter[i] << endl;
      }
    }
  }
}
