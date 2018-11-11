#include "node.h"
using namespace std;

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t que;
  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      que.push(new Node(i, counts[i]));
    }
  }
  while (que.size() != 1) {
    Node * p_1 = que.top();
    que.pop();
    Node * p_2 = que.top();
    que.pop();
    que.push(new Node(p_1, p_2));
  }
  return que.top();
}
