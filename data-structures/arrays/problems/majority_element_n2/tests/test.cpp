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
  check(majorityElement({2, 2, 1, 1, 1, 2, 2}) == 2, "finds a majority after cancellations");
  check(majorityElement({3}) == 3, "handles a single element");
  check(majorityElement({-1, -1, -1, 2, 2}) == -1, "handles negative values");
  check(majorityElement({7, 7, 7, 7}) == 7, "handles an all-equal array");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
