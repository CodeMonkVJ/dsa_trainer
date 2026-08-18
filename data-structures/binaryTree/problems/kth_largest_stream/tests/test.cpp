#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  KthLargest s(3, {4, 5, 8, 2});
  vector<int> actual = {s.add(3), s.add(5), s.add(10), s.add(9), s.add(4)};
  bool ok = actual == vector<int>({4, 5, 5, 8, 8});
  dsa_test::emit_case("{\"k\":3,\"initial\":[4,5,8,2],\"adds\":[3,5,10,9,4]}",
                      "[4,5,5,8,8]", ok ? "[4,5,5,8,8]" : "mismatch", ok);
  return ok ? 0 : 1;
}
