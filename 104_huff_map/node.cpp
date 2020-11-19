#include "node.h"
#include <assert.h>

void buildMap_helper(Node * current, BitString b, std::map<unsigned,BitString> & theMap) {
  if (current->sym != NO_SYM) {
    assert(current->left == NULL && current->right == NULL);
    theMap[current->sym] = b;
  }
  else {
    assert(current->left != NULL && current->right != NULL);
    buildMap_helper(current->left, b.plusZero(), theMap);
    buildMap_helper(current->right, b.plusOne(), theMap);
  }
}

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  buildMap_helper(this, b, theMap);
}

