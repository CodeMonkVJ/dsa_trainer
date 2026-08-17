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
  vector<int> first{1, 3, 2, 3, 1};
  check(reversePairs(first) == 2 && first == vector<int>({1, 1, 2, 3, 3}), "counts the standard example and sorts");
  vector<int> second{2, 4, 3, 5, 1};
  check(reversePairs(second) == 3 && second == vector<int>({1, 2, 3, 4, 5}), "counts cross-half pairs");
  vector<int> extremes{INT_MAX, INT_MIN, 0};
  check(reversePairs(extremes) == 2, "uses 64-bit comparisons");
  vector<int> empty;
  check(reversePairs(empty) == 0 && empty.empty(), "handles an empty array");
  vector<int> ordered{1, 2, 3, 4};
  check(reversePairs(ordered) == 0 && ordered == vector<int>({1, 2, 3, 4}), "handles no reverse pairs");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
