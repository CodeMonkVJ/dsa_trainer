#include <bits/stdc++.h>
using namespace std;

static long long mergeSortAndCount(vector<int>& nums, vector<int>& scratch, int left, int right) {
  if (right - left <= 1) return 0;
  const int middle = left + (right - left) / 2;
  long long count = mergeSortAndCount(nums, scratch, left, middle);
  count += mergeSortAndCount(nums, scratch, middle, right);

  int rightIndex = middle;
  for (int leftIndex = left; leftIndex < middle; ++leftIndex) {
    while (rightIndex < right && static_cast<long long>(nums[leftIndex]) > 2LL * nums[rightIndex]) {
      ++rightIndex;
    }
    count += rightIndex - middle;
  }

  int first = left;
  int second = middle;
  int output = left;
  while (first < middle && second < right) {
    if (nums[first] <= nums[second]) scratch[output++] = nums[first++];
    else scratch[output++] = nums[second++];
  }
  while (first < middle) scratch[output++] = nums[first++];
  while (second < right) scratch[output++] = nums[second++];
  copy(scratch.begin() + left, scratch.begin() + right, nums.begin() + left);
  return count;
}

long long reversePairs(vector<int>& nums) {
  vector<int> scratch(nums.size());
  return mergeSortAndCount(nums, scratch, 0, static_cast<int>(nums.size()));
}

int main() { return 0; }
