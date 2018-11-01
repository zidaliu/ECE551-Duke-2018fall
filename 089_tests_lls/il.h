#ifndef _IL_H_
#define _IL_H_

#include <cstdlib>
void testList(void);
class IntList
{
 private:
  class Node
  {
   public:
    int data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  IntList();
  IntList(const IntList & rhs);
  IntList & operator=(const IntList & rhs);
  ~IntList();
  void addFront(const int & item);
  void addBack(const int & item);
  bool remove(const int & item);
  int & operator[](int index);
  const int & operator[](int index) const;
  int find(const int & item);
  int getSize() const;
  friend void testList(void);
};

void testList(void) {
  IntList a;
  if (a.getSize() != 0) {
    exit(EXIT_FAILURE);
  }

  a.addFront(2);
  a.addFront(3);
  a.addBack(4);
  IntList b(a);   //copy construct
  IntList c = a;  //assignment operator

  //TEST CASE original test case
  if (a.head->data != 3 || a.head->next->data != 2 || a.getSize() != 3 ||
      a.head->next->next->next != NULL || a.head->prev != NULL || a.tail->prev->data != 2 ||
      a.tail->data != 4) {
    exit(EXIT_FAILURE);
  }
  //copy construct test case
  if (b.head->data != 3 || b.head->next->data != 2 || b.getSize() != 3 ||
      b.head->next->next->next != NULL || b.head->prev != NULL || b.tail->prev->data != 2 ||
      b.tail->data != 4) {
    exit(EXIT_FAILURE);
  }
  //assignment operator test case
  if (c.head->data != 3 || c.head->next->data != 2 || c.getSize() != 3 ||
      c.head->next->next->next != NULL || c.head->prev != NULL || c.tail->prev->data != 2 ||
      c.tail->data != 4) {
    exit(EXIT_FAILURE);
  }

  //TEST CASE deep copy
  a.remove(3);
  a.remove(2);
  if (a.getSize() != 1 || a.head->data != 4 || a.tail->data != 4 || a.head->next != NULL ||
      a.head->prev != NULL) {
    exit(EXIT_FAILURE);
  }

  //after remove
  c = a;
  if (c.getSize() != 1 || c.head->data != 4 || c.tail->data != 4 || c.head->next != NULL ||
      c.head->prev != NULL) {
    exit(EXIT_FAILURE);
  }
  //REMOVE LAST element
  c.remove(4);
  if (c.getSize() != 0 || c.head != NULL || c.tail != NULL) {
    exit(EXIT_FAILURE);
  }
}

#endif
