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
  check(findRepeatingMissing({4, 3, 6, 2, 1, 1}) == make_pair(1, 5),
        "finds repeated one and missing five");
  check(findRepeatingMissing({1, 2, 2, 4}) == make_pair(2, 3),
        "handles a repeated middle value");
  check(findRepeatingMissing({2, 2}) == make_pair(2, 1),
        "handles the smallest non-empty case");
  check(findRepeatingMissing({1, 2, 3, 4, 5, 6, 7, 8, 8, 10}) == make_pair(8, 9),
        "handles a larger range");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
