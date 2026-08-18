#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const vector<Edge> edges = {{0, 1, 4}, {1, 2, -2}, {0, 2, 5}};
  const vector<long long> expected = {0, 4, 2};
  const auto actual = bellmanFord(3, edges, 0);
  const bool ok = actual == expected;
  cout << "DSA_CASE "
          "{\"input\":{\"vertices\":3,\"edges\":[[0,1,4],[1,2,-2],[0,2,5]],"
          "\"source\":0},\"expected\":[0,4,2],\"actual\":["
       << actual[0] << "," << actual[1] << "," << actual[2]
       << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS bellman_ford\n" : "FAIL bellman_ford\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
