#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  auto first = kthLargest({3, 2, 1, 5, 6, 4}, 2),
       second = kthLargest({3, 2, 3, 1, 2, 4, 5, 5, 6}, 4);
  bool ok = first == 5 && second == 4;
  dsa_test::emit_case("{\"cases\":[{\"values\":[3,2,1,5,6,4],\"k\":2},{"
                      "\"values\":[3,2,3,1,2,4,5,5,6],\"k\":4}]}",
                      "[5,4]", ok ? "[5,4]" : "mismatch", ok);
  return ok ? 0 : 1;
}
