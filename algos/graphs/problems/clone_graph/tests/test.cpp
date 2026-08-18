#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  Node a(1), b(2), c(3);
  a.neighbors = {&b, &c};
  b.neighbors = {&a};
  Node *copy = cloneGraph(&a);
  const bool ok = copy && copy != &a && copy->val == 1 &&
                  copy->neighbors.size() == 2 && copy->neighbors[0] != &b;
  cout << "DSA_CASE "
          "{\"input\":{\"nodes\":[1,2,3],\"edges\":[[1,2],[1,3],[2,1]]},"
          "\"expected\":{\"root\":1,\"neighbor_count\":2,\"deep_copy\":true},"
          "\"actual\":{\"root\":"
       << (copy ? copy->val : -1)
       << ",\"neighbor_count\":" << (copy ? copy->neighbors.size() : 0)
       << ",\"deep_copy\":"
       << (copy && copy != &a && copy->neighbors[0] != &b ? "true" : "false")
       << "},\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS clone_graph\n" : "FAIL clone_graph\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
