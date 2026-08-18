#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const bool bipartite = isBipartiteBfs({{1}, {0, 2}, {1}});
  const bool nonBipartite = isBipartiteBfs({{1, 2}, {0, 2}, {0, 1}});
  const bool ok = bipartite && !nonBipartite;
  cout << "DSA_CASE "
          "{\"input\":{\"graphs\":[[[1],[0,2],[1]],[[1,2],[0,2],[0,1]]]},"
          "\"expected\":[true,false],\"actual\":["
       << (bipartite ? "true" : "false") << ","
       << (nonBipartite ? "true" : "false")
       << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS bipartite_bfs\n" : "FAIL bipartite_bfs\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
