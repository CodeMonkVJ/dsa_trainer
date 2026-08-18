#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int main() {
  const vector<vector<char>> grid = {
      {'1', '1', '0'}, {'0', '1', '0'}, {'0', '0', '1'}};
  const int actual = numberOfIslands(grid);
  const bool ok = actual == 2;
  cout << "DSA_CASE "
          "{\"input\":{\"grid\":[[\"1\",\"1\",\"0\"],[\"0\",\"1\",\"0\"],["
          "\"0\",\"0\",\"1\"]]},\"expected\":2,\"actual\":"
       << actual << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS number_of_islands\n" : "FAIL number_of_islands\n");
  cout << "DSA_RESULT {\"passed\":" << (ok ? 1 : 0) << ",\"total\":1}\n";
  return ok ? 0 : 1;
}
