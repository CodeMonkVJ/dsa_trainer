#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = longestIncreasingSubsequence({10, 9, 2, 5, 3, 7, 101, 18});
  bool ok = actual == 4;
  dsa_test::emit_case("{\"values\":[10,9,2,5,3,7,101,18]}", "4",
                      to_string(actual), ok);
  cout << (ok ? "PASS lis\n" : "FAIL lis\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
