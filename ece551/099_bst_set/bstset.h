#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node(K k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  // constructor
  BstSet() : root(NULL) {}
  // rule of three : non trivial destructor
  void destroy(Node * root) {
    if (root != NULL) {
      destroy(root->left);
      destroy(root->right);
      delete root;
    }
  }
  virtual ~BstSet<K>() { destroy(root); }
  // rule of three : copy constructor
  Node * copyNode(Node * root) {
    if (root == NULL) {
      return NULL;
    }
    if (root->left == NULL && root->right == NULL) {
      return new Node(root->key);
    }
    else {
      Node * newRoot = new Node(root->key);
      newRoot->left = copyNode(root->left);
      newRoot->right = copyNode(root->right);
      return newRoot;
    }
  }
  BstSet(const BstSet<K> & rhs) : root(NULL) { root = copyNode(rhs.root); }
  // rule of three : copy assignment constructor
  BstSet<K> & operator=(const BstSet<K> & rhs) {
    if (this != &rhs) {
      Node * tempRoot = copyNode(rhs.root);
      destroy(root);
      root = tempRoot;
    }
    return *this;
  }
  // add a node in tree, use ptr to ptr to node method
  virtual void add(const K & key) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if (key < (*cur)->key) {
        cur = &(*cur)->left;
      }
      else if (key == (*cur)->key) {
        return;
      }
      else {
        cur = &(*cur)->right;
      }
    }
    *cur = new Node(key);
  }
  // search in tree iteratively
  virtual bool contains(const K & key) const {
    Node * cur = root;
    while (cur != NULL) {
      if (key == cur->key) {
        return true;
      }
      else if (key < cur->key) {
        cur = cur->left;
      }
      else {
        cur = cur->right;
      }
    }
    return false;
  }
  // remove node
  Node * removeHelper(Node * root, const K & key) {
    if (root == NULL) {
      return NULL;
    }
    if (key < root->key) {
      root->left = removeHelper(root->left, key);
    }
    else if (key > root->key) {
      root->right = removeHelper(root->right, key);
    }
    else {
      Node * temp_left = root->left;
      Node * temp_right = root->right;
      if (root->left == NULL) {
        delete root;
        return temp_right;
      }
      else if (root->right == NULL) {
        delete root;
        return temp_left;
      }
      else {
        // replace the node with the smallest bigger one
        Node * cur = root->right;
        while (cur->left != NULL) {
          cur = cur->left;
        }
        cur->left = root->left;
        delete root;
        return temp_right;
      }
    }
    return root;
  }
  virtual void remove(const K & key) { root = removeHelper(root, key); }
};
