#include <bits/stdc++.h>
using namespace std;

long long maxSubarraySum(const vector<int>& nums) {
  if (nums.empty()) return 0;
  long long bestEnding = nums[0];
  long long best = nums[0];
  for (size_t i = 1; i < nums.size(); ++i) {
    bestEnding = max(static_cast<long long>(nums[i]), bestEnding + nums[i]);
    best = max(best, bestEnding);
  }
  return best;
}
