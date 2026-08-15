#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
bool validOrder(const vector<vector<int>>& graph, const vector<int>& order) {
  if (order.size() != graph.size()) return false;
  vector<int> position(graph.size(), -1);
  for (size_t i = 0; i < order.size(); ++i) position[order[i]] = i;
  for (size_t from = 0; from < graph.size(); ++from) for (int to : graph[from]) if (position[from] >= position[to]) return false;
  return true;
}
int main() {
  vector<vector<int>> graph(6); graph[5] = {2, 0}; graph[4] = {0, 1}; graph[2] = {3}; graph[3] = {1};
  auto order = topologicalSort(graph); check(validOrder(graph, order), "DAG ordering");
  vector<vector<int>> cycle(3); cycle[0] = {1}; cycle[1] = {2}; cycle[2] = {0}; bool rejected = false;
  try { (void)topologicalSort(cycle); } catch (const logic_error&) { rejected = true; }
  check(rejected, "cycle detection");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
