#include <bits/stdc++.h>
using namespace std;

bool twoSum(const vector<int>& nums, int target, int* first, int* second) {
  unordered_map<int, int> seen;
  for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
    auto it = seen.find(target - nums[i]);
    if (it != seen.end()) {
      if (first) *first = it->second;
      if (second) *second = i;
      return true;
    }
    seen.emplace(nums[i], i);
  }
  return false;
}

int main() {
  vector<int> nums{2, 7, 11, 15};
  int first = -1, second = -1;
  cout << twoSum(nums, 9, &first, &second) << ' ' << first << ' ' << second << '\n';
  return 0;
}
