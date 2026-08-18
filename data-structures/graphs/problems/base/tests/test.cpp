#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
string vectorJson(const vector<int> &values) {
  string json = "[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i)
      json += ',';
    json += to_string(values[i]);
  }
  return json + ']';
}
void check(bool ok, const char *name, const char *input, const char *expected,
           const string &actual) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}
int main() {
  Graph graph(6);
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 4);
  const auto bfs = graph.bfs(0);
  check(bfs == vector<int>({0, 1, 2, 3, 4}), "breadth-first traversal",
        "{\"vertices\":6,\"edges\":[[0,1],[0,2],[1,3],[2,4]],\"start\":0}",
        "[0,1,2,3,4]", vectorJson(bfs));
  const auto dfs = graph.dfs(0);
  check(dfs == vector<int>({0, 1, 3, 2, 4}), "depth-first traversal",
        "{\"vertices\":6,\"edges\":[[0,1],[0,2],[1,3],[2,4]],\"start\":0}",
        "[0,1,3,2,4]", vectorJson(dfs));
  bool rejected = false;
  try {
    (void)graph.bfs(6);
  } catch (const out_of_range &) {
    rejected = true;
  }
  check(rejected, "invalid vertex",
        "{\"vertices\":6,\"operation\":[\"bfs\",6]}",
        "{\"throws\":\"out_of_range\"}",
        rejected ? "{\"throws\":\"out_of_range\"}" : "{\"throws\":null}");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
