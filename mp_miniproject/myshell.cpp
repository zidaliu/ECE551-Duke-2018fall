#include "myshell.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>

#include "parse.h"
using namespace std;

void divided(string temp, string & command, string & pameters);

int main() {
  while (1) {
    cout << "myShell$";
    char c;
    vector<char> a;
    pid_t pid;
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

    cout << "Before fork is " << temp << endl;
    /*fork一个子进程*/
    pid = fork();
    if (pid < 0) {
      perror("fork error");
      exit(0);
    }
    else if (pid > 0) {
      //父进程
      Parents parent(pid);
    }
    else {
      //子进程
      string commond;
      string parameters;
      divided(temp, commond, parameters);
      if (parameters.length() <= 0) {
        Child child(pid, commond);  //no parmeters
        child.execute();
      }
      else {  //has parmeters
        vector<string> final_parameter = getparmeter(parameters);
        Child child(pid, commond, final_parameter);
        child.execute();
      }  //子进程正常退出
      return 0;
    }
  }
}
