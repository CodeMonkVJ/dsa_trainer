#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const vector<vector<int>> graph = {{1, 2}, {3}, {3}, {}};
  const vector<int> expected = {0, 1, 2, 3};
  const auto actual = bfsTraversal(graph, 0);
  const bool ok = actual == expected;
  cout << "DSA_CASE "
          "{\"input\":{\"graph\":[[1,2],[3],[3],[]],\"start\":0},\"expected\":["
          "0,1,2,3],\"actual\":["
       << actual[0] << "," << actual[1] << "," << actual[2] << "," << actual[3]
       << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS bfs_traversal\n" : "FAIL bfs_traversal\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
