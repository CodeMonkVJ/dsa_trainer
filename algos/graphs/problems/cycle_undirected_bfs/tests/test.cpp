#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const bool tree = hasUndirectedCycleBfs({{1}, {0, 2}, {1}});
  const bool cycle = hasUndirectedCycleBfs({{1, 2}, {0, 2}, {0, 1}});
  const bool ok = !tree && cycle;
  cout << "DSA_CASE "
          "{\"input\":{\"graphs\":[[[1],[0,2],[1]],[[1,2],[0,2],[0,1]]]},"
          "\"expected\":[false,true],\"actual\":["
       << (tree ? "true" : "false") << "," << (cycle ? "true" : "false")
       << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS cycle_undirected_bfs\n" : "FAIL cycle_undirected_bfs\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
