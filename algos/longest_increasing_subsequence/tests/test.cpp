#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
bool increasing(const vector<int>& values) { for (size_t i = 1; i < values.size(); ++i) if (values[i - 1] >= values[i]) return false; return true; }
int main() {
  auto result = longestIncreasingSubsequence({10, 9, 2, 5, 3, 7, 101, 18});
  check(result.size() == 4 && increasing(result), "classic LIS length and order");
  result = longestIncreasingSubsequence({2, 2, 2});
  check(result.size() == 1, "strictly increasing duplicates");
  check(longestIncreasingSubsequence({}).empty(), "empty input");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
