#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name, const char *input, const char *expected,
           const char *actual) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
bool validOrder(const vector<vector<int>> &graph, const vector<int> &order) {
  if (order.size() != graph.size())
    return false;
  vector<int> position(graph.size(), -1);
  for (size_t i = 0; i < order.size(); ++i)
    position[order[i]] = i;
  for (size_t from = 0; from < graph.size(); ++from)
    for (int to : graph[from])
      if (position[from] >= position[to])
        return false;
  return true;
}
int main() {
  vector<vector<int>> graph(6);
  graph[5] = {2, 0};
  graph[4] = {0, 1};
  graph[2] = {3};
  graph[3] = {1};
  auto order = topologicalSort(graph);
  const bool valid = validOrder(graph, order);
  check(valid, "DAG ordering", "{\"graph\":[[],[ ],[3],[1],[0,1],[2,0]]}",
        "{\"valid_topological_order\":true}",
        valid ? "{\"valid_topological_order\":true}"
              : "{\"valid_topological_order\":false}");
  vector<vector<int>> cycle(3);
  cycle[0] = {1};
  cycle[1] = {2};
  cycle[2] = {0};
  bool rejected = false;
  try {
    (void)topologicalSort(cycle);
  } catch (const logic_error &) {
    rejected = true;
  }
  check(rejected, "cycle detection", "{\"graph\":[[1],[2],[0]]}",
        "{\"throws\":\"logic_error\"}",
        rejected ? "{\"throws\":\"logic_error\"}" : "{\"throws\":null}");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
