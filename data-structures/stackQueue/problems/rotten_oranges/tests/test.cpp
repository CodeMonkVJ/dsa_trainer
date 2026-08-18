#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << std::endl;
  std::string input = std::string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(input, ok ? "true" : "false", ok ? "true" : "false", ok);
}

int main() {
  check(orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}) == 4,
        "multi-source spread");
  check(orangesRotting({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}) == -1,
        "unreachable fresh orange");
  check(orangesRotting({{0, 2}}) == 0, "no fresh oranges");
  check(orangesRotting({{1}}) == -1, "fresh without rotten source");
  check(orangesRotting({}) == 0, "empty grid");
  check(orangesRotting({{2, 1}, {1, 1}}) == 2, "small rectangular grid");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
