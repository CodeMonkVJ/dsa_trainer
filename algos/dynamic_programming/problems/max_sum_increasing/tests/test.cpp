#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = maxSumIncreasing({1, 101, 2, 3, 100, 4, 5});
  bool ok = actual == 106;
  dsa_test::emit_case("{\"values\":[1,101,2,3,100,4,5]}", "106",
                      to_string(actual), ok);
  cout << (ok ? "PASS max_sum_increasing\n" : "FAIL max_sum_increasing\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
