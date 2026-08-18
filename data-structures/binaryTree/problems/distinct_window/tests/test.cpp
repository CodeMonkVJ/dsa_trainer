#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  auto actual = distinctInWindows({1, 2, 1, 3, 4, 3}, 3);
  bool ok = actual == vector<int>({2, 3, 3, 2});
  dsa_test::emit_case("{\"values\":[1,2,1,3,4,3],\"window\":3}", "[2,3,3,2]",
                      ok ? "[2,3,3,2]" : "mismatch", ok);
  return ok ? 0 : 1;
}
