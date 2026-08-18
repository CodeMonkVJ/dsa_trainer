#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int actual = maxProfit({7, 1, 5, 3, 6, 4});
  bool ok = actual == 5;
  dsa_test::emit_case("{\"prices\":[7,1,5,3,6,4]}", "5", to_string(actual), ok);
  cout << (ok ? "PASS stock_buy_sell\n" : "FAIL stock_buy_sell\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
