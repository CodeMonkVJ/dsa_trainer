#include <bits/stdc++.h>
using namespace std;

void nextPermutation(vector<int>& nums) {
  int pivot = static_cast<int>(nums.size()) - 2;
  while (pivot >= 0 && nums[pivot] >= nums[pivot + 1]) --pivot;
  if (pivot >= 0) {
    int successor = static_cast<int>(nums.size()) - 1;
    while (nums[successor] <= nums[pivot]) --successor;
    swap(nums[pivot], nums[successor]);
  }
  reverse(nums.begin() + pivot + 1, nums.end());
}
