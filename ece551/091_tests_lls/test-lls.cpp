#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    IntList il;
    il.addFront(1);
    assert(il.head->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.getSize() == 1);
    il.addFront(2);
    assert(il.head->data == 2);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 1);
    assert(il.tail->data == 1);
    assert(il.tail->prev->data == 2);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il.head->data == 1);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == NULL);
    assert(il.getSize() == 1);
    il.addBack(2);
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.tail->data == 2);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
  }
  // make a IntList object out of scope
  // helper func that uses destructor
  IntList makeList(int i) {
    IntList il;
    il.addBack(i + 1);
    il.addBack(i + 2);
    return il;
  }
  void testCopyCtor() {
    IntList il0 = makeList(0);
    IntList il = il0;
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.tail->data == 2);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
  }
  void testCopyAsgmtOp() {
    // up to this point, copy constructor works well...
    IntList il = makeList(0);
    // case 1: this == &rhs
    il = il;
    assert(il.head->data == 1);
    assert(il.head->prev == NULL);
    assert(il.head->next->data == 2);
    assert(il.tail->data == 2);
    assert(il.tail->prev->data == 1);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
    // from now on, this != &rhs, normal functionality test
    // case 2: assign non-empty list to another non-empty list
    IntList il0 = makeList(2);
    il0.addBack(5);
    il0.addFront(6);
    il0 = il;
    assert(il0.head->data == 1);
    assert(il0.head->prev == NULL);
    assert(il0.head->next->data == 2);
    assert(il0.tail->data == 2);
    assert(il0.tail->prev->data == 1);
    assert(il0.tail->next == NULL);
    assert(il0.getSize() == 2);
    // case 3: assign empty to non-empty
    IntList il1;
    IntList il2 = makeList(0);
    il2 = il1;
    assert(il2.getSize() == 0);
    assert(il2.head == NULL);
    assert(il2.tail == NULL);
    // case 4: assign non-empty to empty
    IntList il3 = makeList(0);
    il1 = il3;
    assert(il1.getSize() == 2);
    assert(il1.head->data == 1);
    assert(il1.head->next->data == 2);
    assert(il1.head->next == il1.tail);
  }
  void testRemove() {
    bool res;
    // case 1: empty list
    IntList empty;
    res = empty.remove(0);
    assert(res == false);
    // case 2: remove at front
    IntList il0 = makeList(0);
    res = il0.remove(1);
    assert(res == true);
    assert(il0.head->data == 2);
    assert(il0.tail->data == 2);
    assert(il0.head->prev == NULL);
    assert(il0.tail->prev == NULL);
    assert(il0.head->next == NULL);
    assert(il0.tail->next == NULL);
    assert(il0.find(1) == -1);
    assert(il0.getSize() == 1);
    // case 3: remove at tail
    IntList il1 = makeList(0);
    res = il1.remove(2);
    assert(res == true);
    assert(il1.head->data == 1);
    assert(il1.tail->data == 1);
    assert(il1.head->prev == NULL);
    assert(il1.tail->prev == NULL);
    assert(il1.head->next == NULL);
    assert(il1.tail->next == NULL);
    assert(il1.find(2) == -1);
    assert(il1.getSize() == 1);
    // case 4: remove in middle
    IntList il2 = makeList(0);
    il2.addBack(3);
    res = il2.remove(2);
    assert(res == true);
    assert(il2.head->data == 1);
    assert(il2.tail->data == 3);
    assert(il2.head->next == il2.tail);
    assert(il2.tail->prev == il2.head);
    assert(il2.head->prev == NULL);
    assert(il2.tail->next == NULL);
    assert(il2.find(2) == -1);
    assert(il2.getSize() == 2);
    // case 5: remove where we have duplicates
    IntList il3 = makeList(0);
    il3.addBack(3);
    il3.addBack(2);
    res = il3.remove(2);
    assert(res == true);
    assert(il3.tail->data == 2);
    assert(il3.head->next->data == 3);
    assert(il3.find(2) == 2);
    assert(il3.getSize() == 3);
    // case 6: remove an element that does not exist
    IntList il4 = makeList(0);
    res = il4.remove(3);
    assert(res == false);
    assert(il4.getSize() == 2);
    // case 7: remove from a list that has only 1 element
    IntList il5;
    il5.addBack(1);
    res = il5.remove(1);
    assert(res == true);
    assert(il5.head == NULL);
    assert(il5.tail == NULL);
    assert(il5.getSize() == 0);
    assert(il5.find(1) == -1);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  t.testAddBack();
  t.testCopyCtor();
  t.testCopyAsgmtOp();
  t.testRemove();
  return EXIT_SUCCESS;
}
