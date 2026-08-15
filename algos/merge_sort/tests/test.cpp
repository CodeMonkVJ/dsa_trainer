#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
bool sorted(const vector<int>& values) { return is_sorted(values.begin(), values.end()); }
int main() {
  vector<int> values{5, 1, 4, 2, 8, 5, -1}; mergeSort(values.data(), values.size());
  check(sorted(values) && values == vector<int>({-1, 1, 2, 4, 5, 5, 8}), "duplicates and negatives");
  mergeSort(nullptr, 0); check(true, "empty array");
  values = {7}; mergeSort(values.data(), 1); check(values == vector<int>({7}), "singleton array");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
