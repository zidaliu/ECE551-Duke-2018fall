#include "myshell.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "parents.h"
#include "parse.h"
using namespace std;

int main() {
  unordered_map<string, int> self_command_list;
  unordered_map<string, string> var_list;
  self_command_list["cd"] = 1;      //self_define operations for specially parent process
  self_command_list["set"] = 2;     //set varble value
  self_command_list["export"] = 3;  //set envir varble
  self_command_list["inc"] = 4;
  while (1) {
    print_path();  //print the current path before $
    char c;
    vector<char> a;
    pid_t pid;
    string temp;

    while ((c = getchar()) != '\n') {
      if (c != EOF) {
        a.push_back(c);
      }
      else {
        cout << endl;  //if the input is EOF then exit the main function
        return 0;
      }
    }
    if (a.size() != 0) {
      a.push_back('\0');
      temp = a.data();
      string exit_line = "exit";  // if the input is exit, then exit the main function
      if (temp == exit_line) {
        return 0;
      }
    }
    else {
      continue;
    }

    string commond;     // record the command
    string parameters;  // record the paramters
    divided(temp, commond, parameters);
    vector<string> final_parameter =
        getparmeter(parameters);  // from the original whole parameters to get every sigle parameter

    //find the real vaule for the var parameter
    find_realvaule(commond, final_parameter, var_list);

    if (self_command_list.find(commond) != self_command_list.end()) {
      switch (self_command_list[commond]) {
        case 1:  //command cd
          change_dir(final_parameter);
          break;
        case 2:  //command set
          set_commond(var_list, parameters, final_parameter);
          break;
        case 3:  //command export
          export_varible(final_parameter, var_list);
          break;
        case 4:  //command inc
          inc_varible(final_parameter, var_list);
          break;
      }
    }
    else if (commond.find('=') != string::npos) {  //set var use "="
      assign_var(commond, final_parameter, var_list);
    }
    else {
      pid = fork();  // fork to get a children process
      if (pid < 0) {
        perror("fork error");
        exit(0);
      }
      else if (pid <= 0) {
        if (parameters.length() <= 0) {
          Child child(pid, commond);  //no parameters input
          child.execute();
        }
        else {                                         //has parmeter
          Child child(pid, commond, final_parameter);  // there is parameter input
          child.execute();
        }  //子进程正常退出
        return 0;
      }
      else {
        Parents parent(pid);  //pid > 0 is the parent process
      }
    }
  }
}
