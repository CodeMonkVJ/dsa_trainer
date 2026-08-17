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
  vector<int> nums{2, 0, 2, 1, 1, 0};
  sort012(nums);
  check(nums == vector<int>({0, 0, 1, 1, 2, 2}), "sorts a mixed array");

  nums = {2, 2, 2};
  sort012(nums);
  check(nums == vector<int>({2, 2, 2}), "handles one repeated value");

  nums = {1, 0, 1};
  sort012(nums);
  check(nums == vector<int>({0, 1, 1}), "handles a short array");

  nums.clear();
  sort012(nums);
  check(nums.empty(), "handles an empty array");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
