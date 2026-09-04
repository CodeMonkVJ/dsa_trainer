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
  Graph graph(7);
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(1, 4);
  graph.addEdge(2, 5);
  graph.addEdge(4, 5);
  
  const auto bfs0 = graph.bfs(0);
  check(bfs0 == vector<int>({0, 1, 2, 3, 4, 5}),
        "breadth-first traversal with cycle",
        "{\"vertices\":7,\"start\":0}",
        "[0,1,2,3,4,5]",
        vectorJson(bfs0));
  
  const auto dfs0 = graph.dfs(0);
  check(dfs0 == vector<int>({0, 1, 3, 4, 5, 2}),
        "depth-first traversal with cycle",
        "{\"vertices\":7,\"start\":0}",
        "[0,1,3,4,5,2]",
        vectorJson(dfs0));
  
  const auto bfs2 = graph.bfs(2);
  check(bfs2 == vector<int>({2, 0, 5, 1, 4, 3}),
        "bfs from nonzero start",
        "{\"vertices\":7,\"start\":2}",
        "[2,0,5,1,4,3]",
        vectorJson(bfs2));
  
  const auto dfs2 = graph.dfs(2);
  check(dfs2 == vector<int>({2, 0, 1, 3, 4, 5}),
        "dfs from nonzero start",
        "{\"vertices\":7,\"start\":2}",
        "[2,0,1,3,4,5]",
        vectorJson(dfs2));
  
  const auto isolatedBfs = graph.bfs(6);
  check(isolatedBfs == vector<int>({6}),
        "isolated vertex bfs",
        "{\"vertices\":7,\"start\":6}",
        "[6]",
        vectorJson(isolatedBfs));
  
  const auto isolatedDfs = graph.dfs(6);
  check(isolatedDfs == vector<int>({6}),
        "isolated vertex dfs",
        "{\"vertices\":7,\"start\":6}",
        "[6]",
        vectorJson(isolatedDfs));
  
  {
    Graph ordered(4);
    ordered.addEdge(0, 2);
    ordered.addEdge(0, 1);
    ordered.addEdge(0, 3);
  
    const auto bfs = ordered.bfs(0);
    check(bfs == vector<int>({0, 2, 1, 3}),
          "preserves adjacency insertion order in bfs",
          "{\"vertices\":4,\"edges\":[[0,2],[0,1],[0,3]],\"start\":0}",
          "[0,2,1,3]",
          vectorJson(bfs));
  
    const auto dfs = ordered.dfs(0);
    check(dfs == vector<int>({0, 2, 1, 3}),
          "preserves adjacency insertion order in dfs",
          "{\"vertices\":4,\"edges\":[[0,2],[0,1],[0,3]],\"start\":0}",
          "[0,2,1,3]",
          vectorJson(dfs));
  }
  
  {
    Graph cyclic(3);
    cyclic.addEdge(0, 1);
    cyclic.addEdge(1, 2);
    cyclic.addEdge(2, 0);
  
    const auto bfs = cyclic.bfs(0);
    check(bfs == vector<int>({0, 1, 2}),
          "cycle visits each vertex once",
          "{\"vertices\":3,\"cycle\":true,\"start\":0}",
          "[0,1,2]",
          vectorJson(bfs));
  }
  
  {
    Graph selfLoop(2);
    selfLoop.addEdge(0, 0);
    selfLoop.addEdge(0, 1);
  
    const auto bfs = selfLoop.bfs(0);
    check(bfs == vector<int>({0, 1}),
          "self loop does not duplicate traversal",
          "{\"vertices\":2,\"edges\":[[0,0],[0,1]],\"start\":0}",
          "[0,1]",
          vectorJson(bfs));
  }
  
  {
    bool threw = false;
    try {
      (void)graph.bfs(-1);
    } catch (const out_of_range &) {
      threw = true;
    }
  
    check(threw,
          "rejects negative bfs start",
          "{\"operation\":[\"bfs\",-1]}",
          "{\"throws\":\"out_of_range\"}",
          threw ? "{\"throws\":\"out_of_range\"}" : "{\"throws\":null}");
  }
  
  {
    bool threw = false;
    try {
      (void)graph.dfs(7);
    } catch (const out_of_range &) {
      threw = true;
    }
  
    check(threw,
          "rejects dfs start past vertex range",
          "{\"operation\":[\"dfs\",7]}",
          "{\"throws\":\"out_of_range\"}",
          threw ? "{\"throws\":\"out_of_range\"}" : "{\"throws\":null}");
  }
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
