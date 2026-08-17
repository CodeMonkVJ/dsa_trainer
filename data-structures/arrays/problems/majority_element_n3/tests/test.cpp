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
  check(majorityElements({3, 2, 3}) == vector<int>({3}), "finds one frequent value");
  check(majorityElements({1, 1, 1, 3, 3, 2, 2, 2}) == vector<int>({1, 2}), "finds two frequent values in order");
  check(majorityElements({1, 2, 3, 4}) == vector<int>({}), "rejects values at the threshold");
  check(majorityElements({}) == vector<int>({}), "handles an empty array");
  check(majorityElements({-2, -2, -2, 5, 5, 7}) == vector<int>({-2}), "handles negative candidates");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
