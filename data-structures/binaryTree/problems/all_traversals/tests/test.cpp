#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  TreeNode a(1), b(2), c(3), d(4);
  a.left = &b;
  a.right = &c;
  b.right = &d;
  auto t = allTraversals(&a);
  const bool preorder_ok = t.preorder == vector<int>({1, 2, 4, 3});
  const bool inorder_ok = t.inorder == vector<int>({2, 4, 1, 3});
  const bool postorder_ok = t.postorder == vector<int>({4, 2, 3, 1});
  auto serialize = [](const vector<int> &values) {
    ostringstream out;
    out << '[';
    for (size_t i = 0; i < values.size(); ++i) {
      if (i)
        out << ',';
      out << values[i];
    }
    out << ']';
    return out.str();
  };
  auto serialize_all = [&serialize](const auto &value) {
    return std::string("{\"preorder\":") + serialize(value.preorder) +
           ",\"inorder\":" + serialize(value.inorder) +
           ",\"postorder\":" + serialize(value.postorder) + "}";
  };
  dsa_test::emit_case("{\"tree\":[1,2,3,null,4],\"traversal\":\"preorder\"}",
                      "[1,2,4,3]", serialize(t.preorder), preorder_ok);
  dsa_test::emit_case("{\"tree\":[1,2,3,null,4],\"traversal\":\"inorder\"}",
                      "[2,4,1,3]", serialize(t.inorder), inorder_ok);
  dsa_test::emit_case("{\"tree\":[1,2,3,null,4],\"traversal\":\"postorder\"}",
                      "[4,2,3,1]", serialize(t.postorder), postorder_ok);
  auto e = allTraversals(nullptr);
  const bool second_ok =
      e.preorder.empty() && e.inorder.empty() && e.postorder.empty();
  dsa_test::emit_case("{\"tree\":null}",
                      "{\"preorder\":[],\"inorder\":[],\"postorder\":[]}",
                      serialize_all(e), second_ok);
  if (!preorder_ok || !inorder_ok || !postorder_ok || !second_ok)
    return 1;
  cout << "DSA_RESULT {\"passed\":"
       << (preorder_ok + inorder_ok + postorder_ok + second_ok)
       << ",\"total\":4}\n";
}
