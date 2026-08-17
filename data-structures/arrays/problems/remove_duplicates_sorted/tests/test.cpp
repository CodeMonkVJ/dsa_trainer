#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }

int main() {
  vector<int> nums{0, 0, 1, 1, 1, 2, 2, 3};
  int k = removeDuplicatesSorted(nums);
  check(k == 4 && vector<int>(nums.begin(), nums.begin() + k) == vector<int>{0, 1, 2, 3}, "compacts repeated values");
  nums = {5, 5, 5};
  k = removeDuplicatesSorted(nums);
  check(k == 1 && nums[0] == 5, "reduces an all-equal input");
  nums = {-2, 0, 4};
  k = removeDuplicatesSorted(nums);
  check(k == 3 && vector<int>(nums.begin(), nums.begin() + k) == vector<int>{-2, 0, 4}, "keeps an already unique input");
  nums.clear();
  check(removeDuplicatesSorted(nums) == 0, "handles an empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
