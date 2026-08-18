#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int p = 0, t = 0;
void c(bool ok, const char *input, const char *expected) {
  ++t;
  if (ok)
    ++p;
  dsa_test::emit_case(input, expected, ok ? "true" : "false", ok);
}
set<vector<string>> q(vector<vector<string>> v) { return {v.begin(), v.end()}; }
int main() {
  auto a = partition("aab");
  c(q(a) == q({{"a", "a", "b"}, {"aa", "b"}}), R"({"text":"aab"})",
    R"({"partitions":[["a","a","b"],["aa","b"]]})");
  auto b = partition("aba");
  c(q(b) == q({{"a", "b", "a"}, {"aba"}}), R"({"text":"aba"})",
    R"({"partitions":[["a","b","a"],["aba"]]})");
  auto d = partition("");
  c(d.size() == 1, R"({"text":""})", R"({"partitions":[[]]})");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p == t ? 0 : 1;
}
