#include <vector>
using namespace std;
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <unordered_map>

/*this fuction is to judge whether the var is a legal var name
input:
     string var
output:
     bool true or false
*/
bool legal_varname(string var) {
  bool status = true;     // record wether the name is legal
  vector<int> legalASCI;  //record the ASCI code of a char
  for (int n = 48; n < 58; n++) {
    legalASCI.push_back(n);  //add"0~9"
  }
  for (int i = 65; i < 91; i++) {  //add"A~Z"
    legalASCI.push_back(i);
  }
  legalASCI.push_back(95);  //add "_"
  for (int j = 97; j < 123; j++) {
    legalASCI.push_back(j);  //a~z
  }
  for (size_t k = 0; k < var.length(); k++) {  //Judge the varble name iteratly
    int ascii;
    ascii = var[k];
    if (count(legalASCI.begin(), legalASCI.end(), ascii) == 0) {
      status = false;
    }
  }
  return status;
}
/*judge the varible's value whether is a number based on 10, this is for inc function
input:
     string str
output:
     bool true or false
*/
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

/* this is the function for inc operator
input:
      vector<string> var, this is the parameters list
      unordered_map<string, string> & var_list this is the variable list
*/
void inc_varible(vector<string> var, unordered_map<string, string> & var_list) {
  if (var.size() < 1) {
    cout << "inc at least one var" << endl;
  }
  for (size_t i = 0; i < var.size(); i++) {
    if (var_list.find(var[i]) ==
        var_list.end()) {  // if we haven't set the varible, set it to 0 and increase it to 1
      var_list[var[i]] = "1";
    }
    else {
      if (isNum(var_list[var[i]])) {             // is a number based on 10
        int n = atoi(var_list[var[i]].c_str());  //change the string to int
        n++;
        stringstream ss;
        ss << n;
        ss >> var_list[var[i]];
      }
      else {
        var_list[var[i]] = "1";  // if not based on 10 then set number as "1"
      }
    }
  }
}

/* this is the function for export operator
input:
      vector<string> var, this is the parameters list
      unordered_map<string, string> & var_list this is the variable list
*/
void export_varible(vector<string> var, unordered_map<string, string> & var_list) {
  if (var.size() < 1) {
    cout << "export at least one var" << endl;
  }
  else {
    for (size_t i = 0; i < var.size(); i++) {
      if (var_list.find(var[i]) == var_list.end()) {  // if the var hasn't been set
        cout << "please set (" << var[i] << ") first!" << endl;
      }
      else {
        setenv(var[i].c_str(), var_list[var[i]].c_str(), 1);
      }
    }
  }
}

/* this is the function for set operator
input:
      vector<string> var, this is the parameters list
      unordered_map<string, string> & var_list this is the variable list
*/
void set_commond(unordered_map<string, string> & var_list,
                 string var_value,
                 vector<string> final_parameters) {
  if (var_value.find(' ') != string::npos) {
    size_t found = var_value.find(' ');
    string key = var_value.substr(0, found);  //this is var name
    string value = var_value.substr(
        found +
        1);  //this is the orignal value of the var but could contains $var, so we have to change it.
    string temp;
    size_t k = 1;
    bool status =
        false;  //status equaling to false means a new parameter start, whcih is set when detect a space.
    for (size_t i = 0; i < value.length(); i++) {
      if (value[i] == ' ') {  //sensitive to " "
        if (i == 0) {
          temp = temp + value[i];
          status = false;
        }
        if (value[i - 1] != '\\' && (i >= 1)) {
          temp = temp + value[i];  //sensitive to "\ "
          status = false;
        }
      }
      else if ((value[i] != ' ') && (status == false)) {
        if (k < final_parameters.size()) {
          temp = temp + final_parameters[k];  //put the parameters in with its original order
          k++;
          status = true;
        }
      }
    }
    value = temp;
    if (legal_varname(key)) {
      var_list[key] = value;  //set the key as the new vaule
    }
    else {
      cout << key << " is a ilegal var name" << endl;
    }
  }
  else {
    cout << "set commond need a value for your varible" << endl;
  }
}

/*this function is used for command cd*/
void change_dir(vector<string> parameters) {
  if (parameters.size() == 0) {
    return;
  }
  else if (parameters.size() == 1) {
    int i = chdir(parameters[0].c_str());
    if (i == -1) {
      char * mesg = strerror(errno);  //cd to a ilvaild route
      cout << mesg << endl;
    }
    return;
  }
  else {
    cout << "You input multi_dir, input again" << endl;
  }
}

/*print the current route before "$" */
void print_path() {
  char * path = NULL;
  path = getcwd(NULL, 0);
  cout << "myShell:" << path << "$";
  free(path);
}

void split_var(string command, string & var, string & value);

/*this function is used for "=” operator
input: 
     string command
     vector<string> parameter, this for multi inputs
     unorder_map<string, string> & var_list*/
void assign_var(string commond,
                vector<string> parmeters,
                unordered_map<string, string> & var_list) {
  string var;
  string value;
  split_var(commond, var, value);  //split var and vaule with "="
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

/*this funtion is used to get the index if "$"
EX: ZIDA$var$var2 the index of $ is 4, 8
then we can get the var and replace them to its vaule
*/
void get_keyindex(string temp, vector<int> & index_list) {
  //  cout << "in 160 temp is " << temp << endl;
  while (temp.find('$') != string::npos) {
    int index = temp.find('$');
    index_list.push_back(index);
    temp[index] =
        'a';  //if we find the first $ then replace it to an arbitrary char so that recording the new $ next time
  }
}

/*this function is for add charactor behind the var*/
bool add_charactor(string commond,
                   unordered_map<string, string> var_list,
                   vector<string> & value_list) {
  bool status = false;
  string true_var = commond;

  unordered_map<string, string>::iterator p;
  for (p = var_list.begin(); p != var_list.end(); p++) {
    if (true_var.find(p->first) != string::npos) {
      value_list.push_back(p->second +
                           true_var.substr(true_var.find(p->first) + (p->first).length()));
      status = true;
      break;
    }
  }
  if (status == false) {
    value_list.push_back("$" + commond);
  }

  return status;
}

/*this function is to get the var name(could be vaild or not) from your input and replace the varible with its value 
EX: I am $var1$var2$var3
    it will store "var1" "var2" "var3" in the var_list
    and find the coresponding vaule in the vaule_list
 input:
    string commond (your input)
    unordered_map<string, string> var_list
    vector<string> & value_list
*/
int get_value_list(string commond,
                   unordered_map<string, string> var_list,
                   vector<string> & value_list) {
  vector<int> index_list;  //record the index of "$" in the commond
  get_keyindex(commond, index_list);

  size_t i = 0;
  string key;
  for (i = 0; i < index_list.size() - 1;
       i++) {  //the key is for the middle vars(In EX is var1 var2)
    key = commond.substr(index_list[i] + 1, (index_list[i + 1] - 1 - index_list[i]));
    if (var_list.find(key) != var_list.end()) {  //if find the key in var_list directly
      value_list.push_back(var_list[key]);
    }
    else {
      if (add_charactor(key, var_list, value_list) ==
          false) {  // find whether the part of it in the var_list
        cout << "uninitalized var (" << key << ")" << endl;
      }
    }
  }

  key = commond.substr(index_list[i] + 1);     //the key is for the last var(In EX is var3)
  if (var_list.find(key) != var_list.end()) {  //if find the key in var_list directly
    value_list.push_back(var_list[key]);
  }
  else {
    if (add_charactor(key, var_list, value_list) ==
        false) {  //find whether the part of it in the var_list
      cout << "uninitalized var (" << key << ")" << endl;
    }
  }
  return 0;
}

/*this function is replace the orignal command and parameter to the real one(which change the var to its vaule) 
EX: var1=at var2=./README
    c$var1 $var2
    then:
    cat ./README
 input:
    string commond (your input command)
    vector<string> & final_parameter (your input parameters)
    vector<string> & value_list (ture vaule for var in order)
*/

void find_realvaule(string & commond,
                    vector<string> & final_parameter,
                    unordered_map<string, string> var_list) {
  if (commond.find("$") != string::npos) {               // if find "$" then we substitude it
    string head = commond.substr(0, commond.find("$"));  // record the content before "$"
    vector<string> value_list;                           //record the value in its var order
    if (get_value_list(commond.substr(commond.find("$")), var_list, value_list) == 0) {
      commond = head;
      for (size_t i = 0; i < value_list.size(); i++) {
        commond = commond + value_list[i];  //recontruct the command
      }
    }
  }

  /*for parameters (the same as command)*/
  for (size_t j = 0; j < final_parameter.size(); j++) {
    if (final_parameter[j].find("$") != string::npos) {
      string head = final_parameter[j].substr(0, final_parameter[j].find("$"));
      vector<string> value_list;
      if (get_value_list(
              final_parameter[j].substr(final_parameter[j].find("$")), var_list, value_list) == 0) {
        final_parameter[j] = head;
        for (size_t i = 0; i < value_list.size(); i++) {
          final_parameter[j] = final_parameter[j] + value_list[i];
        }
      }
    }
  }
}
