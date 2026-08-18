#include <bits/stdc++.h>
using namespace std;

class LFUCache {
  struct Entry { int value; int frequency; list<int>::iterator position; };
  int capacity_, minimum_frequency_ = 0;
  unordered_map<int, Entry> entries_;
  unordered_map<int, list<int>> keys_by_frequency_;

  void promote(unordered_map<int, Entry>::iterator it) {
    int key = it->first;
    int old_frequency = it->second.frequency;
    auto& old_list = keys_by_frequency_[old_frequency];
    old_list.erase(it->second.position);
    if (old_list.empty()) {
      keys_by_frequency_.erase(old_frequency);
      if (minimum_frequency_ == old_frequency) ++minimum_frequency_;
    }
    ++it->second.frequency;
    auto& new_list = keys_by_frequency_[it->second.frequency];
    new_list.push_front(key);
    it->second.position = new_list.begin();
  }

 public:
  explicit LFUCache(int capacity) : capacity_(max(0, capacity)) {}

  int get(int key) {
    auto it = entries_.find(key);
    if (it == entries_.end()) return -1;
    int value = it->second.value;
    promote(it);
    return value;
  }

  void put(int key, int value) {
    if (capacity_ == 0) return;
    auto it = entries_.find(key);
    if (it != entries_.end()) {
      it->second.value = value;
      promote(it);
      return;
    }
    if ((int)entries_.size() == capacity_) {
      auto& victims = keys_by_frequency_[minimum_frequency_];
      int victim = victims.back();
      victims.pop_back();
      if (victims.empty()) keys_by_frequency_.erase(minimum_frequency_);
      entries_.erase(victim);
    }
    minimum_frequency_ = 1;
    auto& frequency_one = keys_by_frequency_[1];
    frequency_one.push_front(key);
    entries_[key] = Entry{value, 1, frequency_one.begin()};
  }
};

int main() {
  LFUCache cache(2);
  cache.put(1, 1); cache.put(2, 2);
  cout << cache.get(1) << '\n';
  cache.put(3, 3);
  cout << cache.get(2) << '\n';
  return 0;
}
