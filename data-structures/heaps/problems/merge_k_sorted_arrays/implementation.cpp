#include <bits/stdc++.h>
using namespace std;

vector<int> mergeKSortedArrays(const vector<vector<int>>& arrays) {
  struct Entry {
    int value;
    size_t array;
    size_t index;
    bool operator>(const Entry& other) const { return value > other.value; }
  };
  priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
  size_t total = 0;
  for (size_t i = 0; i < arrays.size(); ++i) {
    total += arrays[i].size();
    if (!arrays[i].empty()) pending.push({arrays[i][0], i, 0});
  }

  vector<int> result;
  result.reserve(total);
  while (!pending.empty()) {
    Entry current = pending.top();
    pending.pop();
    result.push_back(current.value);
    size_t next = current.index + 1;
    if (next < arrays[current.array].size())
      pending.push({arrays[current.array][next], current.array, next});
  }
  return result;
}
