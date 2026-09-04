#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(const vector<int> &values, int target, int expected,
           const char *name) {
  const int actual = countSubarraysWithXor(values, target);
  ++total;
  cout << "DSA_CASE {\"input\":{\"values\":[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      cout << ',';
    cout << values[i];
  }
  cout << "],\"target\":" << target << "},\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"passed\":" << (actual == expected ? "true" : "false") << "}\n";
  const bool ok = actual == expected;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({4, 2, 2, 6, 4}, 6, 4, "counts the standard example");
  
  check({5, 5, 5}, 0, 2, "counts multiple equal-prefix ranges");
  
  check({1, 2, 3}, 7, 0, "returns zero with no matching range");
  
  check({}, 0, 0, "handles an empty input");
  
  check({6}, 6, 1, "single element matches target");
  
  check({6}, 0, 0, "single element does not match zero target");
  
  check({0}, 0, 1, "single zero matches zero target");
  
  check({0, 0, 0}, 0, 6, "all zero subarrays match zero target");
  
  check({1, 1}, 0, 1, "two equal values xor to zero");
  
  check({1, 1, 1}, 1, 4, "counts repeated matching prefixes");
  
  check({1, 2, 3}, 0, 1, "counts full-array xor zero");
  
  check({2, 2, 2, 2}, 0, 4, "counts even-length zero-xor ranges");
  
  check({2, 2, 2, 2}, 2, 6, "counts odd-length target-xor ranges");
  
  check({1, 2, 1, 2, 1}, 3, 4, "counts overlapping xor ranges");
  
  check({8, 1, 8, 1, 8}, 9, 4, "counts alternating xor ranges");
  
  check({-1}, -1, 1, "handles negative integer xor");
  
  check({-1, -1}, 0, 1, "negative equal values xor to zero");
  
  check({3, 3, 3, 3, 3}, 3, 9, "many repeated target matches");
  
  check({7, 0, 7}, 0, 2, "zero target with repeated prefix xor");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
