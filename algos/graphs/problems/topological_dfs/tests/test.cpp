#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const vector<vector<int>> graph = {{1}, {2}, {}};
  const auto actual = topologicalSortDfs(graph);
  const bool ok = actual == vector<int>({0, 1, 2});
  cout
      << "DSA_CASE "
         "{\"input\":{\"graph\":[[1],[2],[]]},\"expected\":[0,1,2],\"actual\":["
      << actual[0] << "," << actual[1] << "," << actual[2]
      << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS topological_dfs\n" : "FAIL topological_dfs\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
