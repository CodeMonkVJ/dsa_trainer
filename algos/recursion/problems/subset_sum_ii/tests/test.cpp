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
  auto a = subsetsWithDup({1, 2, 2});
  c(q(a) == q({{}, {1}, {2}, {1, 2}, {2, 2}, {1, 2, 2}}),
    R"({"values":[1,2,2]})", R"({"subsets":[[],[1],[2],[1,2],[2,2],[1,2,2]]})");
  auto b = subsetsWithDup({});
  c(b.size() == 1, R"({"values":[]})", R"({"subsets":[[]]})");
  auto d = subsetsWithDup({2, 2, 2});
  c(q(d).size() == 4, R"({"values":[2,2,2]})", R"({"subset_count":4})");
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p == t ? 0 : 1;
}
