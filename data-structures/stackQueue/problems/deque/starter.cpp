#include <bits/stdc++.h>
using namespace std;
class Deque {
  size_t size_ = 0;

public:
  bool empty() const { return size_ == 0; }
  size_t size() const { return size_; }
  void pushFront(int) {}
  void pushBack(int) {}
  bool popFront(int &) { return false; }
  bool popBack(int &) { return false; }
  void clear() { size_ = 0; }
};
