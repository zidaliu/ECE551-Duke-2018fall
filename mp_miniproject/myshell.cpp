#include "myshell.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
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
      string parmeters;
      divided(temp, commond, parmeters);
      Child child(pid, commond);
      child.execute();
      exit(0);  //子进程正常退出
    }
  }
}

void divided(string temp, string & command, string & pameters) {
  int first_space = temp.find(" ");
  if (first_space > 0) {
    command = temp.substr(0, first_space);
    pameters = temp.substr(first_space);
  }
  else {
    command = temp;
  }
}
