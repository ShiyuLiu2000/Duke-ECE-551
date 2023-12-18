#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class Tester;

//YOUR CODE GOES HERE
#include <iostream>
class IndexOutOfBound : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "The requested index is out of bound";
  }
  virtual ~IndexOutOfBound() throw() {}
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;

    //constructors
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & d) : data(d), next(NULL), prev(NULL) {}
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p) {}
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {}
  void addFront(const T & item) {
    if (head == NULL) {
      head = new Node(item);
      tail = head;
    }
    else {
      Node * temp = head;
      head = new Node(item);
      head->next = temp;
      temp->prev = head;
    }
  }
  void addBack(const T & item) {
    if (tail == NULL) {
      tail = new Node(item);
      head = tail;
    }
    else {
      Node * temp = tail;
      tail = new Node(item);
      tail->prev = temp;
      temp->next = tail;
    }
  }
  bool remove(const T & item) {
    Node * cur = head;
    while (cur != NULL) {
      if (cur->data == item) {
        if (cur == head) {
          head = cur->next;
          if (head != NULL) {
            head->prev = NULL;
          }
          if (cur == tail) {
            tail = NULL;
          }
        }
        else if (cur == tail) {
          tail = cur->prev;
          tail->next = NULL;
        }
        else {
          cur->prev->next = cur->next;
          cur->next->prev = cur->prev;
        }
        delete cur;
        return true;
      }
      cur = cur->next;
    }
    return false;
  }
  T & operator[](int index) {
    Node * cur = head;
    try {
      for (int i = 0; i < index; i++) {
        if (cur == NULL || cur->next == NULL) {
          throw IndexOutOfBound();
        }
        cur = cur->next;
      }
    }
    catch (IndexOutOfBound & e) {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    return cur->data;
  }
  const T & operator[](int index) const {
    Node * cur = head;
    try {
      for (int i = 0; i < index; i++) {
        if (cur == NULL || cur->next == NULL) {
          throw IndexOutOfBound();
        }
        cur = cur->next;
      }
    }
    catch (IndexOutOfBound & e) {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    return cur->data;
  }
  int find(const T & item) const {
    Node * cur = head;
    int index = 0;
    while (cur != NULL) {
      if (cur->data == item) {
        return index;
      }
      cur = cur->next;
      index += 1;
    }
    return -1;
  }
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
    if (rhs.head != NULL) {
      head = new Node(rhs.head->data);
    }
    Node * dummy = head;
    Node * cur = rhs.head->next;
    while (cur != NULL && cur->next != NULL) {
      dummy->next = new Node(cur->data);
      dummy->next->prev = dummy;
      dummy = dummy->next;
      cur = cur->next;
    }
    // case where there is only 1 node
    if (cur == NULL) {
      tail = head;
    }
    else {
      tail = new Node(cur->data);
      tail->prev = dummy;
      dummy->next = tail;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      // construct new copied list
      Node * head_temp = NULL;
      Node * tail_temp = NULL;
      if (rhs.head != NULL) {
        head_temp = new Node(rhs.head->data);
        Node * dummy = head_temp;
        Node * cur = rhs.head->next;
        while (cur != NULL && cur->next != NULL) {
          dummy->next = new Node(cur->data);
          dummy->next->prev = dummy;
          dummy = dummy->next;
          cur = cur->next;
        }
        if (cur == NULL) {
          tail_temp = head_temp;
        }
        else {
          tail_temp = new Node(cur->data);
          tail_temp->prev = dummy;
          dummy->next = tail_temp;
        }
        // delete the old list
        cur = head;
        while (cur != NULL) {
          Node * temp = cur->next;
          delete cur;
          cur = temp;
        }
      }
      // assign new value
      head = head_temp;
      tail = tail_temp;
    }
    return *this;
  }
  ~LinkedList() {
    Node * cur = head;
    while (cur != NULL) {
      Node * temp = cur->next;
      delete cur;
      cur = temp;
    }
  }
  int getSize() const {
    int count = 0;
    Node * cur = head;
    while (cur != NULL) {
      count += 1;
      cur = cur->next;
    }
    return count;
  }
  friend class Tester;
};

typedef LinkedList<int> IntList;

#endif
