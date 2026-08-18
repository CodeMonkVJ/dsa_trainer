#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = maxJobProfit({{1, 3, 50}, {2, 4, 10}, {3, 5, 40}, {3, 6, 70}});
  bool ok = actual == 120;
  dsa_test::emit_case("{\"jobs\":[[1,3,50],[2,4,10],[3,5,40],[3,6,70]]}", "120",
                      to_string(actual), ok);
  cout << (ok ? "PASS job scheduling\n" : "FAIL job scheduling\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
