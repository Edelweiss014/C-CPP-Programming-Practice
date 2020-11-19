#include "node.h"

Node *  buildTree(uint64_t * counts) {
  priority_queue_t huff_queue;
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] == 0) continue;
    huff_queue.push(new Node (i, counts[i]));
  }
  if (huff_queue.size() == 0) return NULL;
  while (huff_queue.size() > 1) {
    Node * temp1 = huff_queue.top();
    huff_queue.pop();
    Node * temp2 = huff_queue.top();
    huff_queue.pop();
    huff_queue.push(new Node (temp1, temp2));
  }
  return huff_queue.top();
}  
