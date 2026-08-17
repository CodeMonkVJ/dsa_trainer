#include <bits/stdc++.h>
using namespace std;

int removeDuplicatesSorted(vector<int>& nums) {
  if (nums.empty()) return 0;
  int write = 1;
  for (int read = 1; read < static_cast<int>(nums.size()); ++read)
    if (nums[read] != nums[write - 1]) nums[write++] = nums[read];
  return write;
}

int main() {
  vector<int> nums{0, 0, 1, 1, 2};
  int k = removeDuplicatesSorted(nums);
  cout << k << ": ";
  for (int i = 0; i < k; ++i) cout << nums[i] << ' ';
  cout << '\n';
  return 0;
}
