#include <bits/stdc++.h>
using namespace std;

int longestZeroSumSubarray(const vector<int>& nums) {
  unordered_map<long long, int> first;
  first[0] = -1;
  long long sum = 0;
  int best = 0;
  for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
    sum += nums[i];
    auto [it, inserted] = first.emplace(sum, i);
    if (!inserted) best = max(best, i - it->second);
  }
  return best;
}

int main() { cout << longestZeroSumSubarray({9, -3, 3, -1, 6, -5}) << '\n'; return 0; }
