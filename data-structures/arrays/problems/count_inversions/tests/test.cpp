#include <bits/stdc++.h>
using namespace std;
#include DSA_IMPLEMENTATION

int passed = 0, total = 0;
void check(bool ok, const char* name) {
  ++total;
  if (ok) ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  vector<int> values{5, 3, 2, 4, 1};
  check(countInversions(values) == 8 && values == vector<int>({5, 3, 2, 4, 1}),
        "counts inversions without changing input");
  check(countInversions({1, 2, 3, 4}) == 0, "returns zero for sorted input");
  check(countInversions({4, 3, 2, 1}) == 6, "counts reverse-order pairs");
  check(countInversions({2, 2, 1, 1}) == 4, "does not count equal values as inversions");
  check(countInversions({}) == 0, "handles empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
