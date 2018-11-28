#include <string.h>

#include <iostream>
#include <vector>
using namespace std;

void divided(string temp, string & command, string & pameters);
vector<string> getparmeter(string init_par);
vector<string> reshape(vector<pair<char, int> > record);

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
    }
    //        for(int i =0;i<final_parameter.size();i++){
    //            cout<<final_parameter[i]<<endl;
    //        }
  }
}

void divided(string temp, string & command, string & pameters) {
  // size_t first_space = temp.find(" ");
  //cout << first_space << endl;
  if (string::npos != temp.find(" ")) {
    size_t first_space = temp.find(" ");
    command = temp.substr(0, first_space);
    pameters = temp.substr(first_space + 1);
  }
  else {
    command = temp;
  }
}

vector<string> getparmeter(string parmeter) {
  vector<pair<char, int> > record;
  char slash = '\\';
  for (size_t i = 0; i < parmeter.length(); i++) {
    if (parmeter[i] != slash) {
      pair<char, int> p(parmeter[i], 0);
      record.push_back(p);
    }
    else {
      if (parmeter[i + 1] == ' ') {
        pair<char, int> p(' ', 1);
        record.push_back(p);
        i++;
      }
    }
  }

  for (size_t i = 0; i < record.size(); i++) {
    cout << record[i].first << record[i].second << endl;
  }

  vector<string> final_parameter = reshape(record);
  //        for(int i =0;i<final_parameter.size();i++){
  //            cout<<final_parameter[i]<<endl;
  //        }
  return final_parameter;
}

vector<string> reshape(vector<pair<char, int> > record) {
  vector<string> parameter;
  for (size_t i = 0; i < record.size(); i++) {
    vector<char> temp;
    char space = ' ';
    while ((record[i].first != space || record[i].second == 1) && (i < record.size())) {
      temp.push_back(record[i].first);
      i++;
    }
    if (i >= 1) {
      if (!(record[i - 1].first == space && record[i - 1].second == 0)) {
        char p = '\0';
        temp.push_back(p);
        cout << temp.data() << endl;
        parameter.push_back(temp.data());
      }
    }
  }
  return parameter;
}
