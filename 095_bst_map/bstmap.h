#include <exception>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 protected:
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(const K & key, const V & value) : key(key), value(value), left(NULL), right(NULL) {}
  };

  Node * root;
  Node ** lookupnode(const K & key) const {
    Node ** n = const_cast<Node **>(&root);
    while ((*n)->key != key && *n != NULL) {
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

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) {
    Node ** find = lookupnode(key);
    if (*find == NULL) {
      *find = new Node(key, value);
    }
    else {
      (*find)->value = value;
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node ** find = lookupnode(key);
    if (*find == NULL) {
      throw std::invalid_argument("Not find the key");
    }
    return (*find)->value;
  }

  virtual void remove(const K & key) {
    Node ** find = lookupnode(key);
    Node * temp = *find;
    if (*find == NULL) {
      return;
    }
    if ((*find)->left == NULL) {
      *find = (*find)->right;
    }
    else {
      Node ** change = &(*find)->left;
      while ((*change)->right != NULL) {
        change = &(*change)->right;
      }
      *find = *change;
      *change = (*change)->left;
      (*change)->left = temp->left;
      (*change)->right = temp->right;
    }
    delete temp;
  }
  virtual ~BstMap() { freeNode(root); }
};
