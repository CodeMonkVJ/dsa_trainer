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
  SegmentTree tree({1, 3, 5, 7, 9, 11});
  check(tree.query(0, 5) == 36 && tree.query(1, 4) == 24, "range sums");
  tree.update(2, 10);
  check(tree.query(1, 4) == 29 && tree.query(2, 2) == 10, "point update");
  bool rejected = false;
  try {
    (void)tree.query(-1, 2);
  } catch (const out_of_range &) {
    rejected = true;
  }
  check(rejected, "invalid range");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
