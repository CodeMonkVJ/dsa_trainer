#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  auto input = vector<vector<int>>{{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
  auto actual = floodFill(input, 1, 1, 2);
  auto expected = vector<vector<int>>{{2, 2, 2}, {2, 2, 0}, {2, 0, 1}};
  bool ok = actual == expected;
  dsa_test::emit_case("{\"image\":[[1,1,1],[1,1,0],[1,0,1]],\"row\":1,"
                      "\"column\":1,\"color\":2}",
                      "[[2,2,2],[2,2,0],[2,0,1]]",
                      ok ? "[[2,2,2],[2,2,0],[2,0,1]]" : "mismatch", ok);
  return ok ? 0 : 1;
}
