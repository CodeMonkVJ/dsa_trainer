#include <bits/stdc++.h>
using namespace std;

struct Candidate {
  int frequency;
  int value;
};

vector<int> topKFrequent(const vector<int>& nums, int k) {
  unordered_map<int, int> counts;
  for (int value : nums) ++counts[value];

  // The least desirable selected item is kept at the top so it can be evicted.
  auto worse = [](const Candidate& a, const Candidate& b) {
    if (a.frequency != b.frequency) return a.frequency > b.frequency;
    return a.value < b.value;
  };
  priority_queue<Candidate, vector<Candidate>, decltype(worse)> heap(worse);

  for (const auto& [value, frequency] : counts) {
    heap.push({frequency, value});
    if (static_cast<int>(heap.size()) > k) heap.pop();
  }

  vector<Candidate> selected;
  while (!heap.empty()) {
    selected.push_back(heap.top());
    heap.pop();
  }
  sort(selected.begin(), selected.end(), [](const Candidate& a, const Candidate& b) {
    if (a.frequency != b.frequency) return a.frequency > b.frequency;
    return a.value < b.value;
  });

  vector<int> result;
  result.reserve(selected.size());
  for (const Candidate& candidate : selected) result.push_back(candidate.value);
  return result;
}
