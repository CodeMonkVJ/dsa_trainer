#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) {
  ++total;
  if (ok) ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  vector<int> nums{1, 2, 3};
  nextPermutation(nums);
  check(nums == vector<int>({1, 3, 2}), "advances an increasing permutation");

  nums = {3, 2, 1};
  nextPermutation(nums);
  check(nums == vector<int>({1, 2, 3}), "wraps the largest permutation");

  nums = {1, 1, 5};
  nextPermutation(nums);
  check(nums == vector<int>({1, 5, 1}), "handles duplicate values");

  nums = {7};
  nextPermutation(nums);
  check(nums == vector<int>({7}), "handles a single value");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
