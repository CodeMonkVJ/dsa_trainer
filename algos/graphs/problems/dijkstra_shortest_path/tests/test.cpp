#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name, const char *input, const char *expected,
           const vector<long long> &actual) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":[";
  for (size_t i = 0; i < actual.size(); ++i) {
    if (i)
      cout << ',';
    if (actual[i] == INF)
      cout << "null";
    else
      cout << actual[i];
  }
  cout << "],\"passed\":" << (ok ? "true" : "false") << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
int main() {
  vector<vector<WeightedEdge>> graph(6);
  graph[0] = {{1, 4}, {2, 1}};
  graph[2] = {{1, 2}, {3, 5}};
  graph[1] = {{3, 1}};
  graph[3] = {{4, 3}};
  auto distances = dijkstra(graph, 0);
  check(distances == vector<long long>({0, 3, 1, 4, 7, INF}),
        "weighted paths and unreachable vertex",
        "{\"vertices\":6,\"edges\":[[0,1,4],[0,2,1],[2,1,2],[2,3,5],[1,3,1],[3,"
        "4,3]],\"source\":0}",
        "[0,3,1,4,7,null]", distances);
  const auto single = dijkstra(vector<vector<WeightedEdge>>(1), 0);
  check(single == vector<long long>({0}), "single source vertex",
        "{\"vertices\":1,\"edges\":[],\"source\":0}", "[0]", single);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
