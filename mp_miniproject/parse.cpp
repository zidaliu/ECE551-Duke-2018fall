#include "parse.h"

#include <string.h>

#include <iostream>
#include <vector>

#include "parents.h"
using namespace std;

int main() {
  unordered_map<string, string> var_list;
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
        return 0;
        ;
      }
    }
    if (a.size() != 0) {
      a.push_back('\0');
      temp = a.data();
      string exit_line = "exit";
      if (temp == exit_line) {
        return 0;
      }
    }
    else {
      continue;
    }
    string commond;
    string parameters;
    divided(temp, commond, parameters);
    vector<string> final_parameter = getparmeter(parameters);
    find_realvaule(commond, final_parameter, var_list);

    cout << "aft commond is " << commond << endl;
    for (size_t i = 0; i < final_parameter.size(); i++) {
      cout << "aft parmater is " << final_parameter[i] << endl;
    }
    if (commond.find('=') != string::npos) {
      assign_var(commond, final_parameter, var_list);
    }
  }
  return 0;
}
