#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool ok, const char *name, const string &input,
           const string &expected, const string &actual) {
  ++total;

  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":" << input
       << ",\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

bool validOrder(const vector<vector<int>> &graph,
                const vector<int> &order) {
  if (order.size() != graph.size())
    return false;

  vector<int> position(graph.size(), -1);

  for (size_t i = 0; i < order.size(); ++i) {
    int v = order[i];

    if (v < 0 || v >= static_cast<int>(graph.size()))
      return false;

    if (position[v] != -1)
      return false;

    position[v] = static_cast<int>(i);
  }

  for (size_t from = 0; from < graph.size(); ++from) {
    for (int to : graph[from]) {
      if (position[from] >= position[to])
        return false;
    }
  }

  return true;
}

int main() {
  // Standard DAG
  {
    vector<vector<int>> graph(6);
    graph[5] = {2, 0};
    graph[4] = {0, 1};
    graph[2] = {3};
    graph[3] = {1};

    auto order = topologicalSort(graph);
    bool ok = validOrder(graph, order);

    check(
        ok,
        "standard DAG",
        R"({"graph":[[],[],[3],[1],[0,1],[2,0]]})",
        R"({"valid_topological_order":true})",
        ok ? R"({"valid_topological_order":true})"
           : R"({"valid_topological_order":false})");
  }

  // Empty graph
  {
    vector<vector<int>> graph;

    auto order = topologicalSort(graph);
    bool ok = order.empty();

    check(
        ok,
        "empty graph",
        R"({"graph":[]})",
        "[]",
        order.empty() ? "[]" : R"({"unexpected_nonempty":true})");
  }

  // Single vertex
  {
    vector<vector<int>> graph(1);

    auto order = topologicalSort(graph);
    bool ok = order == vector<int>({0});

    check(
        ok,
        "single vertex",
        R"({"graph":[[]]})",
        "[0]",
        ok ? "[0]" : R"({"wrong_order":true})");
  }

  // Disconnected DAG
  {
    vector<vector<int>> graph(6);
    graph[0] = {1};
    graph[2] = {3};
    graph[4] = {5};

    auto order = topologicalSort(graph);
    bool ok = validOrder(graph, order);

    check(
        ok,
        "disconnected DAG",
        R"({"graph":[[1],[],[3],[],[5],[]]})",
        R"({"valid_topological_order":true})",
        ok ? R"({"valid_topological_order":true})"
           : R"({"valid_topological_order":false})");
  }

  // Multiple zero-indegree starting vertices
  {
    vector<vector<int>> graph(4);
    graph[0] = {2};
    graph[1] = {2};
    graph[2] = {3};

    auto order = topologicalSort(graph);
    bool ok = validOrder(graph, order);

    check(
        ok,
        "multiple starting vertices",
        R"({"graph":[[2],[2],[3],[]]})",
        R"({"valid_topological_order":true})",
        ok ? R"({"valid_topological_order":true})"
           : R"({"valid_topological_order":false})");
  }

  // Simple chain
  {
    vector<vector<int>> graph(5);
    graph[0] = {1};
    graph[1] = {2};
    graph[2] = {3};
    graph[3] = {4};

    auto order = topologicalSort(graph);
    bool ok = order == vector<int>({0, 1, 2, 3, 4});

    check(
        ok,
        "linear chain",
        R"({"graph":[[1],[2],[3],[4],[]]})",
        "[0,1,2,3,4]",
        ok ? "[0,1,2,3,4]" : R"({"wrong_order":true})");
  }

  // Diamond dependency
  {
    vector<vector<int>> graph(4);
    graph[0] = {1, 2};
    graph[1] = {3};
    graph[2] = {3};

    auto order = topologicalSort(graph);
    bool ok = validOrder(graph, order);

    check(
        ok,
        "diamond DAG",
        R"({"graph":[[1,2],[3],[3],[]]})",
        R"({"valid_topological_order":true})",
        ok ? R"({"valid_topological_order":true})"
           : R"({"valid_topological_order":false})");
  }

  // Cycle: expect empty result
  {
    vector<vector<int>> graph(3);
    graph[0] = {1};
    graph[1] = {2};
    graph[2] = {0};

    auto order = topologicalSort(graph);
    bool ok = order.empty();

    check(
        ok,
        "simple cycle",
        R"({"graph":[[1],[2],[0]]})",
        "[]",
        order.empty() ? "[]" : R"({"unexpected_nonempty":true})");
  }

  // Partial DAG plus cycle
  {
    vector<vector<int>> graph(5);
    graph[0] = {1};
    graph[2] = {3};
    graph[3] = {4};
    graph[4] = {2};

    auto order = topologicalSort(graph);
    bool ok = order.empty();

    check(
        ok,
        "disconnected graph with cycle",
        R"({"graph":[[1],[],[3],[4],[2]]})",
        "[]",
        order.empty() ? "[]" : R"({"unexpected_nonempty":true})");
  }

  // Self-loop is a cycle
  {
    vector<vector<int>> graph(2);
    graph[0] = {0};

    auto order = topologicalSort(graph);
    bool ok = order.empty();

    check(
        ok,
        "self loop cycle",
        R"({"graph":[[0],[]]})",
        "[]",
        order.empty() ? "[]" : R"({"unexpected_nonempty":true})");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}