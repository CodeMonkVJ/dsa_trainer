#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  vector<vector<WeightedEdge>> graph(6);
  graph[0] = {{1, 4}, {2, 1}}; graph[2] = {{1, 2}, {3, 5}};
  graph[1] = {{3, 1}}; graph[3] = {{4, 3}};
  auto distances = dijkstra(graph, 0);
  check(distances == vector<long long>({0, 3, 1, 4, 7, INF}), "weighted paths and unreachable vertex");
  check(dijkstra(vector<vector<WeightedEdge>>(1), 0) == vector<long long>({0}), "single source vertex");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
