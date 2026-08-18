#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const int actual = stronglyConnectedComponents({{1}, {2, 3}, {0}, {4}, {}});
  const bool ok = actual == 3;
  cout << "DSA_CASE "
          "{\"input\":{\"graph\":[[1],[2,3],[0],[4],[]]},\"expected\":3,"
          "\"actual\":"
       << actual << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS scc_kosaraju\n" : "FAIL scc_kosaraju\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
