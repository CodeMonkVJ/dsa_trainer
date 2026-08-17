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
  check(maxSubarraySum({-2, 1, -3, 4, -1, 2, 1, -5, 4}) == 6, "finds the best mixed-sign subarray");
  check(maxSubarraySum({-8, -3, -6, -2, -5, -4}) == -2, "keeps the least negative value");
  check(maxSubarraySum({5, 4, -1, 7, 8}) == 23, "handles a subarray spanning most values");
  check(maxSubarraySum({}) == 0, "returns zero for empty input");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
