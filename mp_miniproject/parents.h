#include <vector>
using namespace std;
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>

bool legal_varname(string var) {
  bool status = true;
  vector<int> legalASCI;
  for (int n = 48; n < 58; n++) {
    legalASCI.push_back(n);  //0~9
  }
  for (int i = 65; i < 91; i++) {  //A~Z
    legalASCI.push_back(i);
  }
  legalASCI.push_back(95);  //add "_"
  for (int j = 97; j < 123; j++) {
    legalASCI.push_back(j);  //a~z
  }
  for (size_t k = 0; k < var.length(); k++) {  //judge the varble name
    int ascii;
    ascii = var[k];
    cout << ascii << endl;
    if (count(legalASCI.begin(), legalASCI.end(), ascii) == 0) {
      status = false;
    }
  }
  return status;
}

bool isNum(string str) {
  stringstream sin(str);
  double d;
  char c;
  if (!(sin >> d)) {
    return false;
  }
  if (sin >> c) {
    return false;
  }
  return true;
}

void inc_varible(vector<string> var, unordered_map<string, string> & var_list) {
  if (var.size() < 1) {
    cout << "inc at least one var" << endl;
  }
  for (size_t i = 0; i < var.size(); i++) {
    if (var_list.find(var[i]) == var_list.end()) {
      cout << "please set (" << var[i] << ") first!" << endl;
    }
    else {
      if (isNum(var_list[var[i]])) {
        int n = atoi(var_list[var[i]].c_str());
        n++;
        stringstream ss;
        ss << n;
        ss >> var_list[var[i]];
      }
      else {
        var_list[var[i]] = "1";
      }
    }
  }
}
void export_varible(vector<string> var, unordered_map<string, string> & var_list) {
  if (var.size() < 1) {
    cout << "export at least one var" << endl;
  }
  else {
    for (size_t i = 0; i < var.size(); i++) {
      if (var_list.find(var[i]) == var_list.end()) {
        cout << "please set (" << var[i] << ") first!" << endl;
      }
      else {
        setenv(var[i].c_str(), var_list[var[i]].c_str(), 1);
      }
    }
  }
}
void set_commond(unordered_map<string, string> & var_list, string var_value) {
  if (var_value.find(' ') != string::npos) {
    size_t found = var_value.find(' ');
    string key = var_value.substr(0, found);
    string value = var_value.substr(found + 1);
    var_list[key] = value;
  }
  else {
    cout << "set commond need a value for your varible" << endl;
  }
}

void change_dir(vector<string> parameters) {
  if (parameters.size() == 0) {
    return;
  }
  else if (parameters.size() == 1) {
    int i = chdir(parameters[0].c_str());
    if (i == -1) {
      char * mesg = strerror(errno);
      cout << mesg << endl;
    }
    return;
  }
  else {
    cout << "You input multi_dir, input again" << endl;
  }
}

void print_path() {
  char * path = NULL;
  path = getcwd(NULL, 0);
  cout << "myShell:" << path << "$";
  free(path);
}

void split_var(string command, string & var, string & value);

void assign_var(string commond,
                vector<string> parmeters,
                unordered_map<string, string> & var_list) {
  string var;
  string value;
  split_var(commond, var, value);
  if (legal_varname(var)) {
    var_list[var] = value;
  }
  else {
    cout << var << " is a ilegal var name" << endl;
  }

  for (size_t i = 0; i < parmeters.size(); i++) {
    split_var(parmeters[i], var, value);
    if (legal_varname(var)) {
      var_list[var] = value;
    }
    else {
      cout << var << " is a ilegal var name" << endl;
    }
  }
}

void split_var(string command, string & var, string & value) {
  size_t found = command.find('=');
  var = command.substr(0, found);
  value = command.substr(found + 1);
}

int get_value_list(string commond,
                   unordered_map<string, string> var_list,
                   vector<string> & value_list) {
  string temp = commond;
  vector<int> index_list;
  while (temp.find('$') != string::npos) {
    int index = temp.find('$');
    index_list.push_back(index);
    temp[index] = 'a';
  }

  size_t i = 0;
  string key;
  for (i = 0; i < index_list.size() - 1; i++) {
    key = commond.substr(index_list[i] + 1, index_list[i + 1] - 1);
    if (var_list.find(key) != var_list.end()) {
      value_list.push_back(var_list[key]);
    }
    else {
      return 1;
    }
  }
  key = commond.substr(index_list[i] + 1);
  if (var_list.find(key) != var_list.end()) {
    value_list.push_back(var_list[key]);
  }
  else {
    return 1;
  }
  return 0;
}

void print_value(vector<string> value_list) {
  for (size_t i = 0; i < value_list.size(); i++) {
    cout << value_list[i];
  }
  cout << endl;
}

bool add_charactor(string commond, unordered_map<string, string> var_list) {
  bool status = false;
  string true_var = commond.substr(commond.find('$') + 1);
  unordered_map<string, string>::iterator p;
  for (p = var_list.begin(); p != var_list.end(); p++) {
    if (true_var.find(p->first) != string::npos) {
      cout << p->second << true_var.substr(true_var.find(p->first) + (p->first).length()) << endl;
      status = true;
      break;
    }
  }
  return status;
}
