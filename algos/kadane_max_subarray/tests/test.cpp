#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  auto result = maximumSubarray({-2, 1, -3, 4, -1, 2, 1, -5, 4});
  check(result.sum == 6 && result.left == 3 && result.right == 6, "classic maximum subarray");
  result = maximumSubarray({-8, -3, -6, -2, -5, -4});
  check(result.sum == -2 && result.left == 3 && result.right == 3, "all negative values");
  result = maximumSubarray({5});
  check(result.sum == 5 && result.left == 0 && result.right == 0, "singleton array");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
