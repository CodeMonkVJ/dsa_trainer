#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;
void check(bool ok, const char *input, bool expected) {
  ++total;
  if (ok)
    ++passed;
  dsa_test::emit_case(input, expected ? "true" : "false", ok ? "true" : "false",
                      ok == expected);
}
int main() {
  check(graphColoring({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}}, 2),
        R"({"graph":[[0,1,0],[1,0,1],[0,1,0]],"colors":2})", true);
  check(!graphColoring({{0, 1, 1}, {1, 0, 1}, {1, 1, 0}}, 2),
        R"({"graph":[[0,1,1],[1,0,1],[1,1,0]],"colors":2})", true);
  check(graphColoring({{0, 1, 1}, {1, 0, 1}, {1, 1, 0}}, 3),
        R"({"graph":[[0,1,1],[1,0,1],[1,1,0]],"colors":3})", true);
  check(graphColoring({{0, 0}, {0, 0}}, 1),
        R"({"graph":[[0,0],[0,0]],"colors":1})", true);
  check(graphColoring({}, 0), R"({"graph":[],"colors":0})", true);
  check(!graphColoring({{0, 1}, {1}}, 2), R"({"graph":[[0,1],[1]],"colors":2})",
        true);
  check(!graphColoring({{1}}, 2), R"({"graph":[[1]],"colors":2})", true);
  check(!graphColoring({{0, 2}, {2, 0}}, 2),
        R"({"graph":[[0,2],[2,0]],"colors":2})", true);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
