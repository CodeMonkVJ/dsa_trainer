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
set<vector<int>> q(vector<vector<int>> v) { return {v.begin(), v.end()}; }
int main() {
  auto a = combinationSum({2, 3, 6, 7}, 7);
  c(q(a) == q({{2, 2, 3}, {7}}), R"({"candidates":[2,3,6,7],"target":7})",
    R"({"combinations":[[2,2,3],[7]]})");
  auto b = combinationSum({2}, 1);
  c(b.empty(), R"({"candidates":[2],"target":1})", R"({"combinations":[]})");
  auto d = combinationSum({2, 3, 2}, 4);
  c(q(d) == q({{2, 2}}), R"({"candidates":[2,3,2],"target":4})",
    R"({"combinations":[[2,2]]})");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p == t ? 0 : 1;
}
