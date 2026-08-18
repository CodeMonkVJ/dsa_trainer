#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
  if (k <= 0 || k > static_cast<int>(nums.size())) return {};
  deque<int> candidates;
  vector<int> result;
  for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
    while (!candidates.empty() && candidates.front() <= i - k) candidates.pop_front();
    while (!candidates.empty() && nums[candidates.back()] <= nums[i]) candidates.pop_back();
    candidates.push_back(i);
    if (i >= k - 1) result.push_back(nums[candidates.front()]);
  }
  return result;
}
