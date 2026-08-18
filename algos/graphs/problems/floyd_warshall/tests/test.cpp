#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const long long I = LLONG_MAX / 4;
  const vector<vector<long long>> input = {{0, 3, I}, {I, 0, 2}, {I, I, 0}};
  const auto actual = floydWarshall(input);
  const bool ok = actual[0][2] == 5;
  cout << "DSA_CASE "
          "{\"input\":{\"matrix\":[[0,3,null],[null,0,2],[null,null,0]]},"
          "\"expected\":5,\"actual\":"
       << actual[0][2] << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS floyd_warshall\n" : "FAIL floyd_warshall\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
