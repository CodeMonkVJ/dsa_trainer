#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void printDistances(const vector<long long> &dist) {
  cout << '[';

  for (size_t i = 0; i < dist.size(); ++i) {
    if (i)
      cout << ',';

    if (dist[i] == INF)
      cout << "null";
    else
      cout << dist[i];
  }

  cout << ']';
}

void check(const vector<vector<WeightedEdge>> &graph,
           int source,
           const vector<long long> &expected,
           const char *name) {
  ++total;

  vector<long long> actual;

  bool threw = false;

  try {
    actual = dijkstra(graph, source);
  } catch (...) {
    threw = true;
  }

  bool ok = !threw && actual == expected;

  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"case\":\""
       << name
       << "\",\"source\":"
       << source
       << "},\"expected\":";

  printDistances(expected);

  cout << ",\"actual\":";

  if (threw)
    cout << "\"exception\"";
  else
    printDistances(actual);

  cout << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

void checkThrows(const vector<vector<WeightedEdge>> &graph,
                 int source,
                 const char *name) {
  ++total;

  bool threw = false;

  try {
    (void)dijkstra(graph, source);
  } catch (const invalid_argument &) {
    threw = true;
  } catch (...) {
  }

  if (threw)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"case\":\""
       << name
       << "\",\"source\":"
       << source
       << "},\"expected\":\"invalid_argument\","
       << "\"actual\":\""
       << (threw ? "invalid_argument" : "no exception")
       << "\",\"passed\":"
       << (threw ? "true" : "false")
       << "}\n";

  cout << (threw ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  // Classic case with stale-entry behavior:
  //
  // 0 -> 1 = 4
  // 0 -> 2 = 1
  // 2 -> 1 = 2
  //
  // vertex 1 first gets distance 4, then improves to 3.
  {
    vector<vector<WeightedEdge>> graph(6);

    graph[0] = {{1, 4}, {2, 1}};
    graph[1] = {{3, 1}};
    graph[2] = {{1, 2}, {3, 5}};
    graph[3] = {{4, 3}};

    check(
        graph,
        0,
        {0, 3, 1, 4, 7, INF},
        "weighted paths stale entry and unreachable vertex");
  }

  // Single vertex.
  {
    vector<vector<WeightedEdge>> graph(1);

    check(
        graph,
        0,
        {0},
        "single vertex");
  }

  // Source with no outgoing edges.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[1] = {{2, 5}};
    graph[2] = {{3, 5}};

    check(
        graph,
        0,
        {0, INF, INF, INF},
        "isolated source");
  }

  // Simple directed chain.
  {
    vector<vector<WeightedEdge>> graph(5);

    graph[0] = {{1, 2}};
    graph[1] = {{2, 3}};
    graph[2] = {{3, 4}};
    graph[3] = {{4, 5}};

    check(
        graph,
        0,
        {0, 2, 5, 9, 14},
        "directed chain");
  }

  // Zero-weight edges.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 0}, {2, 10}};
    graph[1] = {{2, 0}};
    graph[2] = {{3, 0}};

    check(
        graph,
        0,
        {0, 0, 0, 0},
        "zero weight edges");
  }

  // Several alternative routes.
  {
    vector<vector<WeightedEdge>> graph(5);

    graph[0] = {{1, 10}, {2, 3}};
    graph[2] = {{1, 1}, {3, 8}, {4, 20}};
    graph[1] = {{3, 2}};
    graph[3] = {{4, 1}};

    check(
        graph,
        0,
        {0, 4, 3, 6, 7},
        "chooses shortest among multiple paths");
  }

  // Parallel edges between same vertices.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[0] = {{1, 10}, {1, 3}, {2, 20}};
    graph[1] = {{2, 4}};

    check(
        graph,
        0,
        {0, 3, 7},
        "parallel edges");
  }

  // Directed nature matters:
  // 0 -> 1 exists, but 1 -> 0 does not.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[0] = {{1, 5}};
    graph[1] = {{2, 7}};

    check(
        graph,
        2,
        {INF, INF, 0},
        "directed edges not assumed bidirectional");
  }

  // Cycle with positive weights.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 1}};
    graph[1] = {{2, 1}};
    graph[2] = {{0, 1}, {3, 1}};

    check(
        graph,
        0,
        {0, 1, 2, 3},
        "positive cycle");
  }

  // Self-loop should not improve distance.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[0] = {{0, 5}, {1, 2}};
    graph[1] = {{2, 3}};

    check(
        graph,
        0,
        {0, 2, 5},
        "positive self loop");
  }

  // Zero-weight self-loop.
  {
    vector<vector<WeightedEdge>> graph(2);

    graph[0] = {{0, 0}, {1, 4}};

    check(
        graph,
        0,
        {0, 4},
        "zero weight self loop");
  }

  // Larger weights: verifies long long distances are used.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 1000000000}};
    graph[1] = {{2, 1000000000}};
    graph[2] = {{3, 1000000000}};

    check(
        graph,
        0,
        {0, 1000000000LL, 2000000000LL, 3000000000LL},
        "distance exceeds int range");
  }

  // Disconnected components.
  {
    vector<vector<WeightedEdge>> graph(6);

    graph[0] = {{1, 2}};
    graph[1] = {{2, 2}};

    graph[3] = {{4, 1}};
    graph[4] = {{5, 1}};

    check(
        graph,
        0,
        {0, 2, 4, INF, INF, INF},
        "disconnected components");
  }

  // Negative edge must be rejected.
  {
    vector<vector<WeightedEdge>> graph(3);

    graph[0] = {{1, 4}};
    graph[1] = {{2, -1}};

    checkThrows(
        graph,
        0,
        "negative edge rejected");
  }

  // Negative edge in an unreachable component should still be rejected
  // if the implementation validates the input graph globally.
  {
    vector<vector<WeightedEdge>> graph(4);

    graph[0] = {{1, 1}};
    graph[2] = {{3, -5}};

    checkThrows(
        graph,
        0,
        "unreachable negative edge rejected");
  }

  // Invalid sources.
  {
    vector<vector<WeightedEdge>> graph(3);

    checkThrows(
        graph,
        -1,
        "negative source rejected");

    checkThrows(
        graph,
        3,
        "source equal to vertex count rejected");
  }

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}