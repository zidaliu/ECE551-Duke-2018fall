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

class Process
{
 protected:
  pid_t pid;
  Process(pid_t a) : pid(a){};
};

class Parents : public Process
{
 public:
  Parents(pid_t pd) : Process(pd) {
    int status;
    printf("This is the parents %d\n", getpid());
    waitpid(pid, &status, 0);  //等待子进程退出
    if (WIFEXITED(status)) {   //正常退出
      printf("Program exited with status %d\n", WEXITSTATUS(status));
    }
    else {
      if (WIFSIGNALED(status)) {  //查看被什么信号关闭
        printf("Program was killed by signal %d\n", WTERMSIG(status));
      }
    }
  }
};

class Child : public Process
{
 private:
  string route;
  vector<string> parameter_list;
  //  unordered_map<string, int> self_command_list;

 public:
  Child(pid_t pd, string a) : Process(pd), route(a), parameter_list(0) {
    printf("This is the child %d\n", getpid());
    // self_command_list["cd"] = 1;
  }

  Child(pid_t pd, string a, vector<string> parameters) : Process(pd), route(a) {
    printf("This is the child %d\n", getpid());
    parameter_list = parameters;
    // self_command_list["cd"] = 1;
  }

  void execute() {
    if (!judge(route)) {  //如果不含有斜杠，就在环境变量中找
      int flag = 0;
      char * env = getenv("PATH");
      cout << "env is " << env << endl;
      vector<string> env_list = split(env);
      for (vector<string>::iterator it = env_list.begin(); it != env_list.end(); ++it) {
        const char * address = (*it).data();
        if (findCommand(address, route)) {  //是否能在指定地址中找到命令，如果找到flag变成1
          flag = 1;
          string ss_address = address;
          string ss_route = route;
          string total_address = ss_address + '/' + ss_route;
          cout << "total_address is " << total_address << endl;
          char * envp[] = {0, NULL};
          char ** argv = new char *[parameter_list.size() + 2];
          construct_parameter(argv, route, parameter_list);
          execve(total_address.c_str(), argv, envp);
          free_pm(argv);
        }
      }
      //  self_func(route, parameter_list, flag);
      if (flag == 0) {  //没到到flag仍然为0
        cout << "Command " << route << " not found" << endl;
      }
    }
    else {  //含有斜杠
      if (check_command(route)) {
        char * envp_1[] = {0, NULL};
        char ** argv = new char *[parameter_list.size() + 2];
        construct_parameter(argv, route, parameter_list);
        int sof;  //successful or fail
        sof = execve(route.c_str(), argv, envp_1);
        free_pm(argv);
        if (sof == -1) {  //fail
          cout << "execv failed" << endl;
          char * mesg = strerror(errno);
          cout << "errno is " << mesg << endl;
        }
      }
    }
  }

  /*  void self_func(string key, vector<string> parameters, int & flag) {
    if (self_command_list.find(key) == self_command_list.end()) {
      flag = 0;
      cout << "not find!" << endl;
    }
    else {
      int record_number = self_command_list[key];
      judge_selfFunc(record_number, parameters);
      flag = 1;
      cout << "find!" << endl;
    }
  }

  void judge_selfFunc(int number, vector<string> parameters) {
    switch (number) {
      case 1:
        change_dir(parameters);
        cout << "find! case1" << endl;
        break;
    }
  }

  void change_dir(vector<string> parameters) {
    if (parameters.size() == 0) {
      return;
    }
    else if (parameters.size() == 1) {
      cout << "run cd" << parameters[0] << endl;
      chdir(parameters[0].c_str());
      return;
    }
    else {
      cout << "Invaild Route " << parameters[0] << endl;
    }
  }
  */
  bool check_command(string route) {
    bool status = true;
    struct stat st;
    const char * path = route.c_str();
    if (lstat(path, &st) < 0) {
      cout << route << " not such file or dir" << endl;
      status = false;
    }
    else {
      if (S_ISDIR(st.st_mode)) {
        cout << route << " is a dir" << endl;
        status = false;
      }
      else if (!S_ISREG(st.st_mode)) {
        cout << route << " not such file or dir" << endl;
        status = false;
      }
    }
    return status;
  };

  void construct_parameter(char **& a, string route, vector<string> parameter_list) {
    char * cstr = new char[route.length() + 1];
    strcpy(cstr, route.c_str());
    a[0] = cstr;
    for (size_t i = 0; i < parameter_list.size(); i++) {
      char * parameter_address = new char[parameter_list[i].length() + 1];
      strcpy(parameter_address, parameter_list[i].c_str());
      a[i + 1] = parameter_address;
    }
    a[parameter_list.size() + 1] = NULL;
  }

  void free_pm(char **& a) {
    int i = 0;
    while (a[i] != NULL) {
      delete[] a[i];
    }
    delete[] a;
  }

  bool judge(string a) {
    string s = a;
    string::size_type idx = s.find("/");
    if (idx == string::npos) {  //不存在
      return false;
    }
    else {  //存在
      return true;
    }
  }

  vector<string> split(char * a) {
    vector<string> single_address;
    const char s[1] = {':'};
    char * token;
    char * saveptr1;
    /* 获取第一个子字符串 */
    token = strtok_r(a, s, &saveptr1);
    /* 继续获取其他的子字符串 */
    while (token != NULL) {
      string ss = token;
      single_address.push_back(ss);
      token = strtok_r(NULL, s, &saveptr1);
    }
    return single_address;
  }

  bool findCommand(const char * path, string instruct) {
    struct dirent * filename;  // return value for readdir()
    DIR * dir;
    bool condition = false;
    dir = opendir(path);
    if (NULL == dir) {
      cout << "Can not open dir " << path << endl;
      exit(1);
    }
    /* read all the files in the dir ~ */
    while ((filename = readdir(dir)) != NULL) {
      if (strcmp(filename->d_name, ".") == 0 || strcmp(filename->d_name, "..") == 0)
        continue;
      string temp1 = filename->d_name;
      string temp2 = instruct;
      if (temp1 == temp2) {
        condition = true;
        break;
      }
    }
    closedir(dir);
    return condition;
  }
  //whether find it in ENV
};
