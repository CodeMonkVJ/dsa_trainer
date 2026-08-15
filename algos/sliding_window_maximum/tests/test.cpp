#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  check(slidingWindowMaximum({1, 3, -1, -3, 5, 3, 6, 7}, 3) == vector<int>({3, 3, 5, 5, 6, 7}), "classic windows");
  check(slidingWindowMaximum({4, 4, 4}, 2) == vector<int>({4, 4}), "duplicate maxima");
  bool rejected = false; try { (void)slidingWindowMaximum({1, 2}, 0); } catch (const invalid_argument&) { rejected = true; }
  check(rejected, "invalid window width");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
