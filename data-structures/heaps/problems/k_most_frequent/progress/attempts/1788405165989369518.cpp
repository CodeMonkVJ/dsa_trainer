#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <utility>
using namespace std;

struct Compare {
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
    if (a.first != b.first) {
      return a.first > b.first;
    }
    return a.second < b.second;
  }
};

vector<int> topKFrequent(const vector<int> &nums, int k) {
  unordered_map<int, int> map;

  for (auto x : nums) {
    if (map.find(x) == map.end())
      map[x] = 1;
    else
      map[x]++;
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

  for (auto x = map.begin(); x != map.end(); x++) {
    pq.push(make_pair(x->second, x->first));
    if (pq.size() > k)
      pq.pop();
  }

  vector<int> ans;
  while (!pq.empty()) {
    int el = pq.top().second;
    ans.push_back(el);
    pq.pop();
  }

  reverse(ans.begin(), ans.end());
  return ans;
}
