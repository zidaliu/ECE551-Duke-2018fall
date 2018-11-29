#include "myshell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "parse.h"
using namespace std;

void divided(string temp, string & command, string & pameters);

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

int main() {
  while (1) {
    print_path();
    char c;
    vector<char> a;
    pid_t pid;
    string temp;
    unordered_map<string, int> self_command_list;
    self_command_list["cd"] = 1;
    while ((c = getchar()) != '\n') {
      if (c != EOF) {
        a.push_back(c);
      }
      else {
        cout << endl;
        return 0;
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

    cout << "Before fork is " << temp << endl;

    //得到参数列表
    string commond;
    string parameters;
    divided(temp, commond, parameters);
    vector<string> final_parameter = getparmeter(parameters);

    /*fork一个子进程*/
    pid = fork();
    if (pid < 0) {
      perror("fork error");
      exit(0);
    }
    else if (pid <= 0) {
      //子进程
      if (self_command_list.find(commond) == self_command_list.end()) {
        if (parameters.length() <= 0) {
          Child child(pid, commond);  //no parmeters
          child.execute();
        }
        else {  //has parmeter
          Child child(pid, commond, final_parameter);
          child.execute();
        }  //子进程正常退出
        return 0;
      }
      else {
        return 0;
      }
    }
    else {
      //父进程
      Parents parent(pid);
      if (self_command_list.find(commond) != self_command_list.end()) {
        switch (self_command_list[commond]) {
          case 1:
            change_dir(final_parameter);
            break;
        }
      }
    }
  }
}
