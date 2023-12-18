#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K k, V v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  // constructor
  BstMap() : root(NULL) {}
  // rule of three : non trivial destructor
  void destroy(Node * root) {
    if (root != NULL) {
      destroy(root->left);
      destroy(root->right);
      delete root;
    }
  }
  virtual ~BstMap() { destroy(root); }
  // rule of three : copy constructor
  Node * copyNode(Node * root) {
    if (root == NULL) {
      return NULL;
    }
    if (root->left == NULL && root->right == NULL) {
      return new Node(root->key, root->value);
    }
    else {
      Node * newRoot = new Node(root->key, root->value);
      newRoot->left = copyNode(root->left);
      newRoot->right = copyNode(root->right);
      return newRoot;
    }
  }
  BstMap(const BstMap<K, V> & rhs) : root(NULL) { root = copyNode(rhs.root); }
  // rule of three : copy assignment constructor
  BstMap<K, V> & operator=(const BstMap<K, V> & rhs) {
    if (this != &rhs) {
      Node * tempRoot = copyNode(rhs.root);
      destroy(root);
      root = tempRoot;
    }
    return *this;
  }
  // add a key-value pair in tree, use ptr to ptr to node method
  virtual void add(const K & key, const V & value) {
    Node ** cur = &root;
    while (*cur != NULL) {
      if (key < (*cur)->key) {
        cur = &(*cur)->left;
      }
      else if (key == (*cur)->key) {
        (*cur)->value = value;
      }
      else {
        cur = &(*cur)->right;
      }
    }
    *cur = new Node(key, value);
  }
  // search in tree iteratively
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * cur = root;
    while (cur != NULL) {
      if (key == cur->key) {
        return cur->value;
      }
      else if (key < cur->key) {
        cur = cur->left;
      }
      else {
        cur = cur->right;
      }
    }
    throw std::invalid_argument("Key not found");
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
