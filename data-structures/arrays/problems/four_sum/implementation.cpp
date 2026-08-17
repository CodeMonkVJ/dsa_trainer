#include <bits/stdc++.h>
using namespace std;

vector<array<int, 4>> fourSum(vector<int> nums, long long target) {
  sort(nums.begin(), nums.end());
  vector<array<int, 4>> result;
  const int n = static_cast<int>(nums.size());
  for (int i = 0; i + 3 < n; ++i) {
    if (i && nums[i] == nums[i - 1]) continue;
    for (int j = i + 1; j + 2 < n; ++j) {
      if (j > i + 1 && nums[j] == nums[j - 1]) continue;
      int left = j + 1, right = n - 1;
      while (left < right) {
        long long sum = static_cast<long long>(nums[i]) + nums[j] + nums[left] + nums[right];
        if (sum == target) {
          result.push_back({nums[i], nums[j], nums[left], nums[right]});
          int leftValue = nums[left], rightValue = nums[right];
          while (left < right && nums[left] == leftValue) ++left;
          while (left < right && nums[right] == rightValue) --right;
        } else if (sum < target) {
          ++left;
        } else {
          --right;
        }
      }
    }
  }
  return result;
}

int main() {
  for (auto q : fourSum({1, 0, -1, 0, -2, 2}, 0))
    cout << q[0] << ' ' << q[1] << ' ' << q[2] << ' ' << q[3] << '\n';
  return 0;
}
