#include <bits/stdc++.h>
using namespace std;

int removeDuplicatesSorted(vector<int>& nums) {
  return 0;
}

int main() {
  vector<int> nums{0, 0, 1, 1, 2};
  int k = removeDuplicatesSorted(nums);
  cout << k << ": ";
  for (int i = 0; i < k; ++i) cout << nums[i] << ' ';
  cout << '\n';
}
