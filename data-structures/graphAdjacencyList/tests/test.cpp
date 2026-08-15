#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  Graph graph(6); graph.addEdge(0, 1); graph.addEdge(0, 2); graph.addEdge(1, 3); graph.addEdge(2, 4);
  check(graph.bfs(0) == vector<int>({0, 1, 2, 3, 4}), "breadth-first traversal");
  check(graph.dfs(0) == vector<int>({0, 1, 3, 2, 4}), "depth-first traversal");
  bool rejected = false; try { (void)graph.bfs(6); } catch (const out_of_range&) { rejected = true; }
  check(rejected, "invalid vertex");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
