#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  MedianStream s;
  s.add(5);
  s.add(1);
  auto first = s.median();
  s.add(9);
  auto second = s.median();
  bool ok = first == 3.0 && second == 5.0;
  dsa_test::emit_case(
      "{\"operations\":[\"add 5\",\"add 1\",\"median\",\"add 9\",\"median\"]}",
      "[3,5]", ok ? "[3,5]" : "mismatch", ok);
  return ok ? 0 : 1;
}
