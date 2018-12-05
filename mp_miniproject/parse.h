/*the head file contain the function that is used for parsing your orignal parameter*/
#include <string.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> reshape(vector<pair<char, int> > record);
vector<string> getparmeter(string parmeter);
void divided(string temp, string & command, string & pameters);

/*divided function using to partition your original input to command part and parameters part
input:
     whole line get from your keyboard
output:
     string command
     string parametrs
*/
void divided(string temp, string & command, string & pameters) {
  int index = 0;
  while (
      temp[index] ==
      ' ') {  //find the first space, which means that you will ignore the any space before the command
    index++;
  }
  string re_temp = temp.substr(index);
  if (string::npos != re_temp.find(" ")) {  // if there is parameters
    size_t first_space = re_temp.find(" ");
    command = re_temp.substr(0, first_space);    // this is command
    pameters = re_temp.substr(first_space + 1);  //this is parametrs
  }
  else {  // if there is no parameters
    command = re_temp;
  }
}

/*getparmeter function using to label your input paramte.
EX: if your input is "\ ", it will ignore "\" and label the " "following "\" as 1, 
so we will retreat it as a plain space rather than ignore it. If it is just a sigle " ", 
we label it as 0, so in the reshape function, 
we will know which " " we should ignore and what we should not ignore.
input:
     string paramters
key midstep:
     vector<pair<char, int> > record, which we label every charactor
output:
     final_parametrs after reshape
*/
vector<string> getparmeter(string parmeter) {
  vector<pair<char, int> > record;
  char slash = '\\';
  for (size_t i = 0; i < parmeter.length(); i++) {
    if (parmeter[i] != slash) {
      pair<char, int> p(parmeter[i], 0);
      record.push_back(p);
    }
    else {
      if (parmeter[i + 1] ==
          ' ') {  //if the char is  "\" and the next char is " " then keep the " " by setting the label as 1
        pair<char, int> p(' ', 1);
        record.push_back(p);
        i++;
      }
    }
  }

  vector<string> final_parameter = reshape(record);
  return final_parameter;
}

/*reshape function is to get the final_parameter list which will ignore " " and keep "\ "
input:
    vector<pair<char, int> > record, which we label every charactor
output:
    final_parametrs after reshape
*/

vector<string> reshape(vector<pair<char, int> > record) {
  vector<string> parameter;
  char space = ' ';
  for (size_t i = 0; i < record.size(); i++) {
    vector<char> temp;
    while (
        (i < record.size()) &&
        (record[i].first != space ||
         record[i].second ==
             1)) {  // if we detect a char that is not " " or is a " " that label is 1, we keep it
      temp.push_back(record[i].first);
      i++;
    }
    if (i >= 1) {
      if (!(record[i - 1].first == space &&
            record[i - 1].second ==
                0)) {  // if we detect a " " with label 0, then we know it is a sperater sign for parameters.
        char p = '\0';  //it is important becasue when use execve it receive c style const char*
        temp.push_back(p);
        parameter.push_back(temp.data());
      }
    }
  }
  return parameter;
}
