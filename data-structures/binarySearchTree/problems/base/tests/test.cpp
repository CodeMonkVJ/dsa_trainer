#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":{\"case\":\"" << name
       << "\"},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
}
int main() {
  BSTree tree;
  bstInit(&tree);
  for (int value : {8, 3, 10, 1, 6, 14, 4, 7, 13})
    bstInsert(&tree, value);
  check(tree.size == 9 && bstContains(&tree, 7) && !bstContains(&tree, 2),
        "insert and search");
  check(!bstInsert(&tree, 7) && bstMin(&tree)->key == 1 &&
            bstMax(&tree)->key == 14,
        "duplicate and min max");
  check(bstHeight(&tree) == 4, "height");
  check(bstRemove(&tree, 1) && bstRemove(&tree, 14) && bstRemove(&tree, 8),
        "leaf and two-child deletion");
  check(!bstContains(&tree, 8) && tree.size == 6,
        "tree remains valid after deletion");
  bstClear(&tree);
  check(tree.root == nullptr && tree.size == 0, "clear");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
