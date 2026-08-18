#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  int first = minEggDrops(2, 10), second = minEggDrops(1, 7);
  bool ok = first == 4 && second == 7;
  dsa_test::emit_case("{\"eggs\":2,\"floors\":10,\"additional_eggs\":1,"
                      "\"additional_floors\":7}",
                      "{\"two_eggs\":4,\"one_egg\":7}",
                      "{\"two_eggs\":" + to_string(first) +
                          ",\"one_egg\":" + to_string(second) + "}",
                      ok);
  cout << (ok ? "PASS egg dropping\n" : "FAIL egg dropping\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
