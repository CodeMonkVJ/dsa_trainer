#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  vector<Item> items{{2, 12}, {1, 10}, {3, 20}, {2, 15}};
  check(maximumValue(items, 5) == 37, "choose best combination once");
  check(maximumValue(items, 0) == 0, "zero capacity");
  check(maximumValue(items, 1) == 10, "single fitting item");
  check(maximumValue(items, 100) == 57, "capacity above total weight");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
