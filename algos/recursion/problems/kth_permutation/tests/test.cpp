#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int p = 0, t = 0;
void c(bool ok, const char *input, const char *expected, const string &actual) {
  ++t;
  if (ok)
    ++p;
  dsa_test::emit_case(input, expected, "\"" + actual + "\"", ok);
}
int main() {
  auto a = getPermutation(3, 1);
  c(a == "123", R"({"n":3,"k":1})", R"("123")", a);
  auto b = getPermutation(3, 4);
  c(b == "231", R"({"n":3,"k":4})", R"("231")", b);
  auto d = getPermutation(3, 6);
  c(d == "321", R"({"n":3,"k":6})", R"("321")", d);
  auto e = getPermutation(3, 7);
  c(e.empty(), R"({"n":3,"k":7})", R"("")", e);
  cout << "DSA_RESULT {\"passed\":" << p << ",\"total\":" << t << "}\n";
  return p == t ? 0 : 1;
}
