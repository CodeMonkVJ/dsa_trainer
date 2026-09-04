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
vector<int> s(vector<int> x) {
  sort(x.begin(), x.end());
  return x;
}

int main() {
  auto a = subsetSums({1, 2, 3});
  c(s(a) == s({0, 1, 2, 3, 3, 4, 5, 6}),
    R"({"values":[1,2,3]})",
    R"({"values":[0,1,2,3,3,4,5,6]})");

  auto b = subsetSums({});
  c(b.size() == 1 && b[0] == 0,
    R"({"values":[]})",
    R"({"values":[0]})");

  auto d = subsetSums({2, 2});
  c(s(d) == s({0, 2, 2, 4}),
    R"({"values":[2,2]})",
    R"({"values":[0,2,2,4]})");

  auto e = subsetSums({5});
  c(s(e) == s({0, 5}),
    R"({"values":[5]})",
    R"({"values":[0,5]})");

  auto f = subsetSums({0});
  c(s(f) == s({0, 0}),
    R"({"values":[0]})",
    R"({"values":[0,0]})");

  auto g = subsetSums({0, 0});
  c(s(g) == s({0, 0, 0, 0}),
    R"({"values":[0,0]})",
    R"({"values":[0,0,0,0]})");

  auto h = subsetSums({-1, 2});
  c(s(h) == s({0, -1, 2, 1}),
    R"({"values":[-1,2]})",
    R"({"values":[-1,0,1,2]})");

  auto i = subsetSums({-2, -3});
  c(s(i) == s({0, -2, -3, -5}),
    R"({"values":[-2,-3]})",
    R"({"values":[-5,-3,-2,0]})");

  auto j = subsetSums({1, -1});
  c(s(j) == s({0, 1, -1, 0}),
    R"({"values":[1,-1]})",
    R"({"values":[-1,0,0,1]})");

  auto k = subsetSums({1, 1, 1});
  c(s(k) == s({0, 1, 1, 1, 2, 2, 2, 3}),
    R"({"values":[1,1,1]})",
    R"({"values":[0,1,1,1,2,2,2,3]})");

  auto l = subsetSums({3, -1, 2});
  c(l.size() == 8 &&
        s(l) == s({0, 3, -1, 2, 2, 5, 1, 4}),
    R"({"values":[3,-1,2]})",
    R"({"values":[-1,0,1,2,2,3,4,5]})");

  cout << "DSA_RESULT {\"passed\":" << p
       << ",\"total\":" << t << "}\n";

  return p == t ? 0 : 1;
}