#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  vector<int> values{9, 4, 7, 3, 10, 5, 5, -2}; quickSort(values, 0, values.size() - 1);
  check(is_sorted(values.begin(), values.end()), "mixed values and duplicates");
  values = {1, 2, 3, 4}; quickSort(values, 0, values.size() - 1); check(is_sorted(values.begin(), values.end()), "already sorted input");
  values.clear(); quickSort(values, 0, -1); check(values.empty(), "empty range");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
