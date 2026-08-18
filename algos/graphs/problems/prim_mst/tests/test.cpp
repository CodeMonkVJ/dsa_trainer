#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const int actual =
      primMst({{{1, 1}, {2, 4}}, {{0, 1}, {2, 2}}, {{0, 4}, {1, 2}}});
  const bool ok = actual == 3;
  cout << "DSA_CASE "
          "{\"input\":{\"graph\":[[[1,1],[2,4]],[[0,1],[2,2]],[[0,4],[1,2]]]},"
          "\"expected\":3,\"actual\":"
       << actual << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS prim_mst\n" : "FAIL prim_mst\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
