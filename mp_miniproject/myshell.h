#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
extern char ** environ;
/*Process has two child class, Parents and Child*/
class Process
{
 protected:
  pid_t pid;  // record current pid
  Process(pid_t a) : pid(a){};
};

class Parents : public Process
{
 public:
  Parents(pid_t pd) : Process(pd) {
    int status;
    // printf("This is the parents %d\n", getpid());
    waitpid(pid, &status, 0);  //wait for it's children process exit
    if (WIFEXITED(status)) {   //exit normally
      printf("Program exited with status %d\n", WEXITSTATUS(status));
    }
    else {
      if (WIFSIGNALED(status)) {  //check the children process was closed by what kind of signal
        printf("Program was killed by signal %d\n", WTERMSIG(status));
      }
    }
  }
};

class Child : public Process
{
 private:
  string route;  //this is the command route which can be a relative route or a absolute one
  vector<string> parameter_list;  //record the parmeters

 public:
  Child(pid_t pd, string a) : Process(pd), route(a), parameter_list(0) {
    // printf("This is the child %d\n", getpid());
  }

  Child(pid_t pd, string a, vector<string> parameters) : Process(pd), route(a) {
    //   printf("This is the child %d\n", getpid());
    parameter_list = parameters;
  }

  void execute() {
    if (!judge(route)) {  //if there is no "/" then find the command in PATH
      int status = 0;     // to record whether we can find it in PATH
      char * env = getenv("PATH");
      vector<string> env_list = split(env);  //split the PATH by ":"
      for (vector<string>::iterator it = env_list.begin(); it != env_list.end(); ++it) {
        const char * address = (*it).data();
        if (findCommand(
                address,
                route)) {  //if we can find the command in the directory then set status to 1
          status = 1;
          string ss_address = address;
          string ss_route = route;
          string total_address = ss_address + '/' + ss_route;
          char ** argv = new char *[parameter_list.size() + 2];
          construct_parameter(argv, route, parameter_list);  //construct argv for execve
          int sof;
          sof = execve(total_address.c_str(), argv, environ);
          if (sof == -1) {  //fail
            cout << "execv failed" << endl;
            char * mesg = strerror(errno);
            cout << "errno is " << mesg << endl;
           }
          free_pm(argv);
       }
      }
      if (status == 0) {  // we cannot find this command in all the directories in PATH
        cout << "Command " << route << " not found" << endl;
      }
    }
    else {  // if there is "/", then excute it directly
      if (check_command(route)) {
        char ** argv = new char *[parameter_list.size() + 2];
        construct_parameter(argv, route, parameter_list);
        int sof;  //excute it successful or fail
        sof = execve(route.c_str(), argv, environ);
        if (sof == -1) {  //fail
          cout << "execv failed" << endl;
          char * mesg = strerror(errno);
          cout << "errno is " << mesg << endl;
        }
        free_pm(argv);
      }
    }
  }

  /*this fuction is to check whether your input command is an excutable file */
  bool check_command(string route) {
    bool status = true;
    struct stat st;
    const char * path = route.c_str();
    if (lstat(path, &st) < 0) {
      cout << route << " not such file or dir" << endl;
      status = false;
    }
    else {
      if (S_ISDIR(st.st_mode)) {  // if you input is a directory
        cout << route << " is a dir" << endl;
        status = false;
      }
      else if (!S_ISREG(st.st_mode)) {
        cout << route << " not such file or dir" << endl;  // if you input is not a regular file
        status = false;
      }
    }
    return status;
  };

  /*this function is to construct the parameters that can be used in execve function*/
  void construct_parameter(char **& a, string route, vector<string> parameter_list) {
    char * cstr = new char[route.length() + 1];  //+1 is because you cannot ignore "\0" in c style
    strcpy(cstr, route.c_str());
    a[0] = cstr;  // the first element in argv should be the command
    for (size_t i = 0; i < parameter_list.size(); i++) {
      char * parameter_address = new char[parameter_list[i].length() + 1];
      strcpy(parameter_address, parameter_list[i].c_str());
      a[i + 1] = parameter_address;  //store parmaters in following elements in argv
    }
    a[parameter_list.size() + 1] = NULL;
  }

  /*free all the allocated memory after excuting*/
  void free_pm(char **& a) {
    int i = 0;
    while (a[i] != NULL) {
      delete[] a[i];
      i++;
    }
    delete[] a;
  }
  /*judge whether your command contains "/"*/
  bool judge(string a) {
    string s = a;
    string::size_type idx = s.find("/");
    if (idx == string::npos) {  //not exist
      return false;
    }
    else {  //exist
      return true;
    }
  }

  /*split PATH by ":" */
  vector<string> split(char * a) {
    vector<string> single_address;  //record the directories in PATH
    const char s[1] = {':'};
    char * token;
    char * saveptr1;
    /* get first substring */
    token = strtok_r(a, s, &saveptr1);
    /* get other substring */
    while (token != NULL) {
      string ss = token;
      single_address.push_back(ss);
      token = strtok_r(NULL, s, &saveptr1);
    }
    return single_address;
  }

  /*whether we can find the command in a directory */
  bool findCommand(const char * path, string instruct) {
    struct dirent * filename;  // return value for readdir()
    DIR * dir;
    bool condition = false;  // set condition as false means we cannot find it by default
    dir = opendir(path);
    if (NULL == dir) {
      cout << "Can not open dir " << path << endl;
      return false;
    }
    /* read all the files in the dir ~ */
    while ((filename = readdir(dir)) != NULL) {
      if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
        continue;
      string temp1 = filename->d_name;
      string temp2 = instruct;
      if (temp1 == temp2) {
        condition = true;  //find the command in the directory
        break;
      }
    }
    closedir(dir);
    return condition;
  }
  //whether find it in ENV
};
