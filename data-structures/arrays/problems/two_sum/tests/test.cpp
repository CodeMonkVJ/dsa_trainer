#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &nums, int target, bool expectedFound,
           pair<int, int> expectedPair, const char *name) {
  int actualA = -1, actualB = -1;
  const bool actualFound = twoSum(nums, target, &actualA, &actualB);
  const bool ok =
      actualFound == expectedFound &&
      (!expectedFound || pair<int, int>{actualA, actualB} == expectedPair);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < nums.size(); ++i) {
    if (i)
      cout << ',';
    cout << nums[i];
  }
  cout << "],\"target\":" << target
       << "},\"expected\":{\"found\":" << (expectedFound ? "true" : "false")
       << ",\"indices\":[" << expectedPair.first << ',' << expectedPair.second
       << "]},\"actual\":{\"found\":" << (actualFound ? "true" : "false")
       << ",\"indices\":[" << actualA << ',' << actualB
       << "]},\"passed\":" << (ok ? "true" : "false") << "}\n";
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({2, 7, 11, 15}, 9, true, {0, 1}, "finds a pair in order");
  check({3, 3, 4}, 6, true, {0, 1},
        "uses two equal values at distinct indices");
  check({1, 2, 3}, 20, false, {-1, -1}, "reports a missing pair");
  check({-4, 9, 13}, 5, true, {0, 1}, "supports output pointers");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
