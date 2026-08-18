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
  auto a = combinationSum2({10, 1, 2, 7, 6, 1, 5}, 8);
  c(q(a) == q({{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}}),
    R"({"values":[10,1,2,7,6,1,5],"target":8})",
    R"({"combinations":[[1,1,6],[1,2,5],[1,7],[2,6]]})");
  auto b = combinationSum2({2, 4}, 1);
  c(b.empty(), R"({"values":[2,4],"target":1})", R"({"combinations":[]})");
  auto d = combinationSum2({1, 1, 1}, 2);
  c(q(d) == q({{1, 1}}), R"({"values":[1,1,1],"target":2})",
    R"({"combinations":[[1,1]]})");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p == t ? 0 : 1;
}
