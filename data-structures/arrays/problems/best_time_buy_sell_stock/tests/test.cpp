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
  check(maxProfit({7, 1, 5, 3, 6, 4}) == 5, "chooses the best later sale");
  check(maxProfit({7, 6, 4, 3, 1}) == 0, "returns zero when prices only fall");
  check(maxProfit({2, 4, 1, 7}) == 6, "updates the minimum buy price");
  check(maxProfit({}) == 0 && maxProfit({5}) == 0, "handles short inputs");

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
