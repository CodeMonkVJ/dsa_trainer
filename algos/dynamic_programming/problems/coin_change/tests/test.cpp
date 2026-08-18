#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int first = coinChange({1, 2, 5}, 11), second = coinChange({2}, 3);
  bool ok = first == 3 && second == -1;
  dsa_test::emit_case("{\"coins\":[1,2,5],\"amount\":11,\"additional_amount\":"
                      "3,\"additional_coins\":[2]}",
                      "{\"amount_11\":3,\"amount_3\":-1}",
                      "{\"amount_11\":" + to_string(first) +
                          ",\"amount_3\":" + to_string(second) + "}",
                      ok);
  cout << (ok ? "PASS coin_change\n" : "FAIL coin_change\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
