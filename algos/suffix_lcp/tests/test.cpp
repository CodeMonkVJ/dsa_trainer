#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  SuffixArray banana("banana");
  check(banana.sa == vector<int>({5, 3, 1, 0, 4, 2}), "banana suffix order");
  check(banana.lcp == vector<int>({1, 3, 0, 0, 2}), "banana neighboring LCP");
  SuffixArray empty(""); check(empty.sa.empty() && empty.lcp.empty(), "empty string");
  SuffixArray repeated("aaaa"); check(repeated.sa == vector<int>({3, 2, 1, 0}) && repeated.lcp == vector<int>({1, 2, 3}), "repeated characters");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
