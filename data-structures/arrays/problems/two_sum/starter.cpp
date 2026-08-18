#include <bits/stdc++.h>
using namespace std;

bool twoSum(const vector<int> &nums, int target, int *first, int *second) {
  return false;
}

int main() {
  vector<int> nums{2, 7, 11, 15};
  int first = -1, second = -1;
  cout << twoSum(nums, 9, &first, &second) << " " << first << " " << second
       << '\n';
}
