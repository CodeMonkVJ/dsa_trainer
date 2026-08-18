#include <bits/stdc++.h>
using namespace std;

class LRUCache {
  int capacity_;
  list<pair<int, int>> order_;
  unordered_map<int, list<pair<int, int>>::iterator> index_;

 public:
  explicit LRUCache(int capacity) : capacity_(max(0, capacity)) {}

  int get(int key) {
    auto it = index_.find(key);
    if (it == index_.end()) return -1;
    order_.splice(order_.begin(), order_, it->second);
    return it->second->second;
  }

  void put(int key, int value) {
    if (capacity_ == 0) return;
    auto it = index_.find(key);
    if (it != index_.end()) {
      it->second->second = value;
      order_.splice(order_.begin(), order_, it->second);
      return;
    }
    if ((int)order_.size() == capacity_) {
      index_.erase(order_.back().first);
      order_.pop_back();
    }
    order_.emplace_front(key, value);
    index_[key] = order_.begin();
  }
};

int main() {
  LRUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cout << cache.get(1) << '\n';
  cache.put(3, 3);
  cout << cache.get(2) << '\n';
  return 0;
}
