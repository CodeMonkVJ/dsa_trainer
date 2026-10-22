#include <bits/stdc++.h>
#include <queue>
using namespace std;

int kthLargest(const vector<int> &values, int k) {
  priority_queue<int, vector<int>, greater<int>> minHeap;

  int n = values.size();
  if (k <= 0 || k > n)
    return -1;

  for (auto val : values) {
    minHeap.push(val);
    if (minHeap.size() > k) {
      minHeap.pop();
    }
  }

  return minHeap.top();
}
