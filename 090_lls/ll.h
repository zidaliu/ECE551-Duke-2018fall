#ifndef _IL_H_
#define _IL_H_
#include <cstdlib>
#include <exception>
void testList(void);
template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(T data) : data(data), next(NULL), prev(NULL) {}
    Node(T data, Node * next) : data(data), next(next), prev(NULL){};
    Node(T data, Node * next, Node * prev) : data(data), next(next), prev(prev){};
  };

  class IndexError : public std::exception
  {
    const char * what() { return "Index out of boundd"; }
  };

  Node * head;
  Node * tail;
  int size;

 protected:
  Node * remove(const T & data, Node * current, bool & a) {
    if (current == NULL) {  //base case: empty list
      return NULL;
    }
    if (data == current->data) {   //base case: node to remove
      Node * ans = current->next;  //answer will be "everything after”
      delete current;              //delete node we are removing
      a = true;
      return ans;
    }
    current->next = remove(data, current->next, a);
    return current;
  }

  T & index(int) const;
  void destory();

 public:
  LinkedList() : head(NULL), tail(NULL){};
  LinkedList(const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs) {
    destory();
    head = NULL;
    tail = NULL;
    for (Node * p = rhs.head; p != NULL; p = p->next) {
      this->addBack(p->data);
    }
    return *this;
  }
  ~LinkedList() { destory(); }
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int i) { return index(i); }
  const T & operator[](int i) const { return index(i); };
  int find(const T & item);
  int getSize() const;
  friend void testList(void);
};

template<typename T>
int LinkedList<T>::getSize() const {
  int i = 0;
  for (Node * p = head; p != NULL; p = p->next) {
    i++;
  }
  return i;
}

template<typename T>
void LinkedList<T>::destory() {
  Node * temp;
  for (Node * p = head; p != NULL; p = temp) {
    temp = p->next;
    delete p;
  }
}

template<typename T>
void LinkedList<T>::addFront(const T & item) {
  head = new Node(item, head);
  if (tail == NULL) {
    tail = head;
  }
  else {
    head->next->prev = head;
  }
  size++;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
  for (Node * p = rhs.head; p != NULL; p = p->next) {
    this->addBack(p->data);
  }
}

template<typename T>
void LinkedList<T>::addBack(const T & item) {
  tail = new Node(item, NULL, tail);
  if (head == NULL) {
    head = tail;
  }
  else {
    tail->prev->next = tail;
  }
  size++;
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  bool state = false;
  head = remove(item, head, state);
  return state;
}

template<typename T>
T & LinkedList<T>::index(int i) const {
  Node * p;
  for (p = head; p != NULL && i > 0; p = p->next) {
    --i;
  }
  if (p == NULL)
    throw IndexError();
  return p->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) {
  int i = 0;
  Node * p;
  for (p = head; p != NULL; p = p->next) {
    if (p->data == item) {
      break;
    }
    i++;
  }
  if (p == NULL) {
    i = -1;
  }
  return i;
}

/*
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

  //check a after mid remove
  a.remove(3);
  a.remove(2);
  if (a.getSize() != 1 || a.head->data != 4 || a.tail->data != 4 || a.head->next != NULL ||
      a.head->prev != NULL) {
    exit(EXIT_FAILURE);
  }

  if (b.head->data != 3 || b.head->next->data != 2 || b.getSize() != 3 ||
      b.head->next->next->next != NULL || b.head->prev != NULL || b.tail->prev->data != 2 ||
      b.tail->data != 4) {
    exit(EXIT_FAILURE);
  }
  if (c.head->data != 3 || c.head->next->data != 2 || c.getSize() != 3 ||
      c.head->next->next->next != NULL || c.head->prev != NULL || c.tail->prev->data != 2 ||
      c.tail->data != 4) {
    exit(EXIT_FAILURE);
  }
  //re assignment c
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
*/
#endif
