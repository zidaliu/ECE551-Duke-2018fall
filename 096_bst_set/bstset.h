#include <exception>

#include "set.h"

template<typename T>
class BstSet : public Set<T>
{
 protected:
  class Node
  {
   public:
    T key;
    Node * left;
    Node * right;
    Node(const T & key) : key(key), left(NULL), right(NULL) {}
  };
  Node * root;
  Node ** lookupnode(const T & key) const {
    Node ** n = const_cast<Node **>(&root);
    while (*n != NULL) {
      if ((*n)->key < key) {
        n = &(*n)->right;
      }
      else if ((*n)->key > key) {
        n = &(*n)->left;
      }
      else {
        break;
      }
    }
    return n;
  }
  void freeNode(Node * n) {
    if (n == NULL) {
      return;
    }

    freeNode(n->left);
    freeNode(n->right);
    delete n;
  }

  void copyTree(Node ** n, const Node * m) {
    if (m != NULL) {
      *n = new Node(m->key);
      copyTree(&(*n)->left, m->left);
      copyTree(&(*n)->right, m->right);
    }
  }

 public:
  BstSet() : root(NULL) {}
  BstSet(const BstSet & m) : root(NULL) { copyTree(&root, m.root); }
  const BstSet & operator=(const BstSet & m) {
    if (&m != this) {
      BstSet temp = m;
      Node * t = root;
      root = temp.root;
      temp.root = t;
    }
    return *this;
  }

  virtual void add(const T & key) {
    Node ** find = lookupnode(key);
    if (*find == NULL) {
      *find = new Node(key);
    }
  }

  virtual bool contains(const T & key) const {
    Node ** find = lookupnode(key);
    if (*find == NULL) {
      return false;
    }
    return true;
  }

  virtual void remove(const T & key) {
    Node ** find = lookupnode(key);
    Node * temp = *find;

    if (*find == NULL) {
      return;
    }
    if ((*find)->left == NULL) {
      *find = (*find)->right;
    }
    else {
      Node ** change = &temp->left;
      while ((*change)->right != NULL) {
        change = &(*change)->right;
      }
      *find = *change;
      *change = (*change)->left;
      (*find)->left = temp->left;
      (*find)->right = temp->right;
    }
    delete temp;
  }

  virtual ~BstSet() { freeNode(root); }
};
