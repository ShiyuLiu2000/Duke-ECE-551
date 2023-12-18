#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t pq;
  // initialize the priority queue by adding all the nodes
  for (int i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  // recursively build the huffman coding tree
  while (pq.size() > 1) {
    Node * left = pq.top();
    pq.pop();
    Node * right = pq.top();
    pq.pop();
    pq.push(new Node(left, right));
  }
  return pq.top();
}
