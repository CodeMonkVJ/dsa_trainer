#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(long long actual, long long expected, const char *name) {
  ++total;

  bool ok = actual == expected;

  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"case\":\"" << name
       << "\"},\"expected\":" << expected
       << ",\"actual\":" << actual
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  // Empty graph.
  check(
      primMst({}),
      0,
      "empty graph");

  // Single vertex has MST weight 0.
  check(
      primMst({{}}),
      0,
      "single vertex");

  // Simple triangle.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[0] = {{1, 1}, {2, 4}};
    graph[1] = {{0, 1}, {2, 2}};
    graph[2] = {{0, 4}, {1, 2}};

    check(
        primMst(graph),
        3,
        "simple triangle");
  }

  // MST should choose 1 + 2 + 1 = 4.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 1}, {2, 4}};
    graph[1] = {{0, 1}, {2, 2}, {3, 5}};
    graph[2] = {{0, 4}, {1, 2}, {3, 1}};
    graph[3] = {{1, 5}, {2, 1}};

    check(
        primMst(graph),
        4,
        "four vertex graph");
  }

  // Several expensive edges; MST should keep only the cheap ones.
  {
    vector<vector<WeightedEdge>> graph(5);

    graph[0] = {{1, 10}, {2, 2}};
    graph[1] = {{0, 10}, {2, 3}, {3, 8}};
    graph[2] = {{0, 2}, {1, 3}, {3, 1}, {4, 7}};
    graph[3] = {{1, 8}, {2, 1}, {4, 4}};
    graph[4] = {{2, 7}, {3, 4}};

    check(
        primMst(graph),
        10,
        "chooses cheapest spanning edges");
  }

  // Negative weights.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, -5}, {2, 2}};
    graph[1] = {{0, -5}, {2, -1}, {3, 4}};
    graph[2] = {{0, 2}, {1, -1}, {3, -3}};
    graph[3] = {{1, 4}, {2, -3}};

    check(
        primMst(graph),
        -9,
        "negative edge weights");
  }

  // Disconnected graph.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 1}};
    graph[1] = {{0, 1}};
    graph[2] = {{3, 2}};
    graph[3] = {{2, 2}};

    check(
        primMst(graph),
        -1,
        "disconnected graph");
  }

  // Vertex 0 is isolated while the other vertices form a component.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[1] = {{2, 5}};
    graph[2] = {{1, 5}};

    check(
        primMst(graph),
        -1,
        "isolated starting vertex");
  }

  // Star graph.
  {
    vector<vector<WeightedEdge>> graph(5);

    graph[0] = {
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4}
    };

    graph[1] = {{0, 1}};
    graph[2] = {{0, 2}};
    graph[3] = {{0, 3}};
    graph[4] = {{0, 4}};

    check(
        primMst(graph),
        10,
        "star graph");
  }

  // Already a tree: MST must equal sum of all edges.
  {
    vector<vector<WeightedEdge>> graph(5);

    graph[0] = {{1, 4}};
    graph[1] = {{0, 4}, {2, 3}};
    graph[2] = {{1, 3}, {3, 2}};
    graph[3] = {{2, 2}, {4, 1}};
    graph[4] = {{3, 1}};

    check(
        primMst(graph),
        10,
        "graph already a tree");
  }

  // Equal-weight edges.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 1}, {2, 1}};
    graph[1] = {{0, 1}, {2, 1}, {3, 1}};
    graph[2] = {{0, 1}, {1, 1}, {3, 1}};
    graph[3] = {{1, 1}, {2, 1}};

    check(
        primMst(graph),
        3,
        "equal weight edges");
  }

  {
    const long long w = 3000000000LL;
  
    vector<vector<WeightedEdge>> graph(3);
  
    graph[0] = {{1, w}, {2, w + 1}};
    graph[1] = {{0, w}, {2, w + 2}};
    graph[2] = {{0, w + 1}, {1, w + 2}};
  
    check(
        primMst(graph),
        2 * w + 1,
        "large edge weights");
  }

  // Multiple edges reaching the same vertex. The cheaper one must win.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[0] = {{1, 10}, {1, 2}, {2, 20}};
    graph[1] = {{0, 10}, {0, 2}, {2, 3}};
    graph[2] = {{0, 20}, {1, 3}};

    check(
        primMst(graph),
        5,
        "multiple edges between vertices");
  }

  // Dense graph with many stale heap entries.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 5}, {2, 1}, {3, 10}};
    graph[1] = {{0, 5}, {2, 2}, {3, 3}};
    graph[2] = {{0, 1}, {1, 2}, {3, 4}};
    graph[3] = {{0, 10}, {1, 3}, {2, 4}};

    check(
        primMst(graph),
        6,
        "stale heap edges");
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}