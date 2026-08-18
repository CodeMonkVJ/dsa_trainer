#include <bits/stdc++.h>
using namespace std;
class SinglyLinkedList {
  size_t size_ = 0;

public:
  ~SinglyLinkedList() {}
  void pushFront(int) {}
  bool insertAfter(int, int) { return false; }
  bool removeFirst(int) { return false; }
  void reverse() {}
  bool contains(int) const { return false; }
  void print() const {}
  void clear() { size_ = 0; }
  size_t size() const { return size_; }
};
