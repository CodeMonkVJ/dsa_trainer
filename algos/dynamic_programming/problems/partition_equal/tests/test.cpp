#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool first = canPartition({1, 5, 11, 5}), second = canPartition({1, 2, 3, 5});
  bool ok = first && !second;
  dsa_test::emit_case(
      "{\"first_values\":[1,5,11,5],\"second_values\":[1,2,3,5]}",
      "{\"first\":true,\"second\":false}",
      "{\"first\":" + string(first ? "true" : "false") +
          ",\"second\":" + string(second ? "true" : "false") + "}",
      ok);
  cout << (ok ? "PASS partition_equal\n" : "FAIL partition_equal\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
