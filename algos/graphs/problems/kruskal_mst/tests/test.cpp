#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const int expected = 3;
  const int actual = kruskalMst(3, {{0, 1, 1}, {1, 2, 2}, {0, 2, 4}});
  const bool ok = actual == expected;
  cout << "DSA_CASE "
          "{\"input\":{\"vertices\":3,\"edges\":[[0,1,1],[1,2,2],[0,2,4]]},"
          "\"expected\":3,\"actual\":"
       << actual << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS kruskal_mst\n" : "FAIL kruskal_mst\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
