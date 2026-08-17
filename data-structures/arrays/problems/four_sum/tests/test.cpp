#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }

int main() {
  auto result = fourSum({1, 0, -1, 0, -2, 2}, 0);
  vector<array<int, 4>> expected{{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
  check(result == expected, "returns sorted unique quadruplets");
  check(fourSum({2, 2, 2, 2, 2}, 8) == vector<array<int, 4>>{{2, 2, 2, 2}}, "deduplicates equal values");
  check(fourSum({1, 2, 3}, 6).empty(), "handles too few values");
  check(fourSum({1000000000, 1000000000, 1000000000, 1000000000}, 4000000000LL).size() == 1, "uses wide sums");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
