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
  check(findDuplicate({1, 3, 4, 2, 2}) == 2, "finds a duplicate in the middle");
  check(findDuplicate({3, 1, 3, 4, 2}) == 3, "finds a duplicate at the start of the cycle");
  check(findDuplicate({1, 1}) == 1, "handles the smallest valid input");
  check(findDuplicate({2, 5, 9, 6, 9, 3, 8, 9, 7, 1}) == 9,
        "handles a value repeated more than twice");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
