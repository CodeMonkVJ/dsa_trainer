#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const vector<vector<int>> &graph,
           bool expected,
           const char *name) {
  ++total;

  bool actual = hasUndirectedCycleBfs(graph);
  bool ok = (actual == expected);

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << (expected ? "true" : "false")
       << " actual=" << (actual ? "true" : "false")
       << '\n';

  cout << "DSA_CASE {\"input\":{\"test\":\""
       << name
       << "\"},\"expected\":"
       << (expected ? "true" : "false")
       << ",\"actual\":"
       << (actual ? "true" : "false")
       << ",\"passed\":"
       << (ok ? "true" : "false")
       << "}\n";
}

int main() {
  // Empty graph.
  check(
      {},
      false,
      "empty graph");

  // Single isolated vertex.
  check(
      {{}},
      false,
      "single isolated vertex");

  // Two isolated vertices.
  check(
      {{}, {}},
      false,
      "multiple isolated vertices");

  // Single edge.
  check(
      {{1}, {0}},
      false,
      "single edge");

  // Simple chain.
  check(
      {{1},
       {0, 2},
       {1}},
      false,
      "simple chain");

  // Longer tree.
  check(
      {{1, 2},
       {0, 3, 4},
       {0},
       {1},
       {1}},
      false,
      "tree with branching");

  // Triangle.
  check(
      {{1, 2},
       {0, 2},
       {0, 1}},
      true,
      "triangle cycle");

  // Four-node cycle.
  check(
      {{1, 3},
       {0, 2},
       {1, 3},
       {0, 2}},
      true,
      "four node cycle");

  // Cycle with a tail attached.
  check(
      {{1},
       {0, 2, 3},
       {1, 3},
       {1, 2, 4},
       {3}},
      true,
      "cycle with tail");

  // Disconnected graph with no cycles.
  check(
      {{1},
       {0},
       {3},
       {2},
       {}},
      false,
      "disconnected acyclic graph");

  // Disconnected graph where only second component has cycle.
  check(
      {{1},
       {0},
       {3, 4},
       {2, 4},
       {2, 3}},
      true,
      "cycle in disconnected component");

  // One tree component and one cyclic component.
  check(
      {{1, 2},
       {0},
       {0},
       {4, 5},
       {3, 5},
       {3, 4}},
      true,
      "tree plus cycle component");

  // Parent edge must not be mistaken for a cycle.
  check(
      {{1},
       {0, 2},
       {1, 3},
       {2}},
      false,
      "parent edges are not cycles");

  // Dense acyclic-looking prefix but actual cycle later.
  check(
      {{1},
       {0, 2},
       {1, 3, 4},
       {2, 4},
       {2, 3}},
      true,
      "cycle found deeper in bfs");

  // Self-loop, if your graph representation allows it.
  check(
      {{0}},
      true,
      "self loop");

  // Isolated component plus self-loop component.
  check(
      {{}, {1}},
      true,
      "self loop in disconnected component");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}