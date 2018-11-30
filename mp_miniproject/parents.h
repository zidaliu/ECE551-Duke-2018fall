#include <vector>
using namespace std;
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <unordered_map>

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
