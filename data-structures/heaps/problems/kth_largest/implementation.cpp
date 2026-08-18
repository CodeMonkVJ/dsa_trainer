#include <bits/stdc++.h>
using namespace std;

int findKthLargest(vector<int> nums, int k) {
  priority_queue<int, vector<int>, greater<int>> smallest;
  for (int value : nums) {
    smallest.push(value);
    if ((int)smallest.size() > k) smallest.pop();
  }
  return smallest.top();
}

int main() { return 0; }
