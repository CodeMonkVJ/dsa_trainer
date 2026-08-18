#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const bool acyclic = hasDirectedCycleDfs({{1}, {2}, {}});
  const bool cyclic = hasDirectedCycleDfs({{1}, {2}, {0}});
  const bool ok = !acyclic && cyclic;
  cout << "DSA_CASE "
          "{\"input\":{\"graphs\":[[[1],[2],[]],[[1],[2],[0]]]},\"expected\":["
          "false,true],\"actual\":["
       << (acyclic ? "true" : "false") << "," << (cyclic ? "true" : "false")
       << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS cycle_directed_dfs\n" : "FAIL cycle_directed_dfs\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
