#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = maxProductSubarray({2, 3, -2, 4});
  bool ok = actual == 6;
  dsa_test::emit_case("{\"values\":[2,3,-2,4]}", "6", to_string(actual), ok);
  cout << (ok ? "PASS max_product_subarray\n" : "FAIL max_product_subarray\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
