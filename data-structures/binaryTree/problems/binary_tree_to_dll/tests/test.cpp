#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  Node n1(1), n2(2), n3(3);
  n2.left = &n1;
  n2.right = &n3;
  Node *h = treeToDoublyList(&n2);
  bool ok = h == &n1 && h->right == &n2 && n2.left == &n1 && n2.right == &n3 &&
            n3.left == &n2 && n3.right == nullptr;
  dsa_test::emit_case(
      "{\"tree\":[2,1,3]}", "{\"forward\":[1,2,3],\"back_links\":true}",
      ok ? "{\"forward\":[1,2,3],\"back_links\":true}" : "mismatch", ok);
  return ok ? 0 : 1;
}
