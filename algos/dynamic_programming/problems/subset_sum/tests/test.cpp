#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  bool first = subsetSum({3, 34, 4, 12, 5, 2}, 9),
       second = subsetSum({3, 34, 4}, 10);
  bool ok = first && !second;
  dsa_test::emit_case("{\"first_values\":[3,34,4,12,5,2],\"first_target\":9,"
                      "\"second_values\":[3,34,4],\"second_target\":10}",
                      "{\"first\":true,\"second\":false}",
                      "{\"first\":" + string(first ? "true" : "false") +
                          ",\"second\":" + string(second ? "true" : "false") +
                          "}",
                      ok);
  cout << (ok ? "PASS subset_sum\n" : "FAIL subset_sum\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
