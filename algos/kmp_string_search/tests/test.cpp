#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  check(findOccurrences("ababcabcabababd", "ababd") == vector<int>({10}), "single occurrence");
  check(findOccurrences("aaaaa", "aaa") == vector<int>({0, 1, 2}), "overlapping occurrences");
  check(findOccurrences("abcdef", "xyz").empty(), "absent pattern");
  check(findOccurrences("abc", "").empty(), "empty pattern");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
