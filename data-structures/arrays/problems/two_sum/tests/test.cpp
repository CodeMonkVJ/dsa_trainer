#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }

int main() {
  int a = -1, b = -1;
  vector<int> nums{2, 7, 11, 15};
  check(twoSum(nums, 9, &a, &b) && a == 0 && b == 1, "finds a pair in order");
  nums = {3, 3, 4};
  check(twoSum(nums, 6, &a, &b) && a == 0 && b == 1, "uses two equal values at distinct indices");
  nums = {1, 2, 3};
  check(!twoSum(nums, 20, &a, &b), "reports a missing pair");
  check(twoSum(vector<int>{-4, 9, 13}, 5, nullptr, nullptr), "supports null output pointers");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
