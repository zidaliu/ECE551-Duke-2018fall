#include <string.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> reshape(vector<pair<char, int> > record);
vector<string> getparmeter(string parmeter);
void divided(string temp, string & command, string & pameters);

void divided(string temp, string & command, string & pameters) {
  int index = 0;
  while (temp[index] == ' ') {
    index++;
  }
  string re_temp = temp.substr(index);
  if (string::npos != re_temp.find(" ")) {
    size_t first_space = re_temp.find(" ");
    command = re_temp.substr(0, first_space);
    pameters = re_temp.substr(first_space + 1);
  }
  else {
    command = re_temp;
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
    //    cout << record[i].first << record[i].second << endl;
  }

  vector<string> final_parameter = reshape(record);
  return final_parameter;
}

vector<string> reshape(vector<pair<char, int> > record) {
  vector<string> parameter;
  char space = ' ';
  for (size_t i = 0; i < record.size(); i++) {
    vector<char> temp;
    while ((i < record.size()) && (record[i].first != space || record[i].second == 1)) {
      temp.push_back(record[i].first);
      i++;
    }
    if (i >= 1) {
      if (!(record[i - 1].first == space && record[i - 1].second == 0)) {
        char p = '\0';
        temp.push_back(p);
        parameter.push_back(temp.data());
      }
    }
  }
  return parameter;
}
