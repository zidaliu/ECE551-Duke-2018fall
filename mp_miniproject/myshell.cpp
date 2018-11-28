#include "myshell.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
using namespace std;

int main() {
  while (1) {
    cout << "myShell$";
    char c;
    vector<char> a;
    pid_t pid;
    char * temp = NULL;
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
      const char * exit_line = "exit";
      if (strcmp(temp, exit_line) == 0) {
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
      Child child(pid, temp);
      child.execute();
      exit(0);  //子进程正常退出
    }
  }
}
