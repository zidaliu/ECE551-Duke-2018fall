#include <iostream>
#include <sstream>
#include <string>

#include "bstmap.h"

int main() {
  BstMap<char, int> m;
  m.add('a', 10);
  m.add('b', 5);
  m.add('c', 15);
  m.add('d', 20);
  m.add('e', 7);
  m.add('f', 21);
  m.lookup('d');
  try {
    m.lookup('m');
  }
  catch (const std::invalid_argument & e) {
    std::cout << e.what() << "\n";
  }
  m.add('m', 23);
  try {
    m.lookup('m');
  }
  catch (const std::invalid_argument & e) {
    std::cout << "Not add successful" << e.what() << "\n";
  }
  m.remove('m');
  try {
    m.lookup('m');
  }
  catch (const std::invalid_argument & e) {
    std::cout << "Now remove sucess " << e.what() << "\n";
  }
  /*copy construct*/
  BstMap<char, int> m_1(m);
  try {
    m_1.lookup('a');
  }
  catch (const std::invalid_argument & e) {
    std::cout << "Not copy sucessful"
              << "\n";
  }

  /*assignment operater*/
  BstMap<char, int> m_2 = m;
  try {
    m_2.lookup('a');
  }
  catch (const std::invalid_argument & e) {
    std::cout << "Not assign sucessful"
              << "\n";
  }

  return 0;
}
