#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const vector<long long> &actual,
           const vector<long long> &expected,
           const char *name) {
  bool ok = actual == expected;

  ++total;
  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

void checkThrows(int vertices,
                 const vector<Edge> &edges,
                 int source,
                 const char *name) {
  bool threw = false;

  try {
    (void)bellmanFord(vertices, edges, source);
  } catch (...) {
    threw = true;
  }

  ++total;
  if (threw)
    ++passed;

  cout << (threw ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  // Basic negative edge, no cycle.
  check(
      bellmanFord(
          3,
          {
              {0, 1, 4},
              {1, 2, -2},
              {0, 2, 5},
          },
          0),
      {0, 4, 2},
      "basic negative edge");

  // Single vertex.
  check(
      bellmanFord(
          1,
          {},
          0),
      {0},
      "single vertex");

  // Unreachable vertices.
  {
    const long long INF = LLONG_MAX;

    check(
        bellmanFord(
            4,
            {
                {0, 1, 5},
                {1, 2, 3},
            },
            0),
        {0, 5, 8, INF},
        "unreachable vertex");
  }

  // Source has no outgoing edges.
  {
    const long long INF = LLONG_MAX;

    check(
        bellmanFord(
            3,
            {
                {1, 2, 5},
            },
            0),
        {0, INF, INF},
        "source isolated");
  }

  // Zero weight edges.
  check(
      bellmanFord(
          4,
          {
              {0, 1, 0},
              {1, 2, 0},
              {2, 3, 0},
          },
          0),
      {0, 0, 0, 0},
      "zero weight chain");

  // Multiple possible paths.
  check(
      bellmanFord(
          4,
          {
              {0, 1, 10},
              {0, 2, 3},
              {2, 1, 1},
              {1, 3, 2},
              {2, 3, 10},
          },
          0),
      {0, 4, 3, 6},
      "later path improves earlier distance");

  // Negative edge makes indirect path better.
  check(
      bellmanFord(
          4,
          {
              {0, 1, 5},
              {0, 2, 2},
              {2, 1, -4},
              {1, 3, 3},
          },
          0),
      {0, -2, 2, 1},
      "negative shortcut");

  // Edge order forces propagation across multiple passes.
  check(
      bellmanFord(
          5,
          {
              {3, 4, 1},
              {2, 3, 1},
              {1, 2, 1},
              {0, 1, 1},
          },
          0),
      {0, 1, 2, 3, 4},
      "requires multiple relaxation passes");

  // Multiple negative edges but no negative cycle.
  check(
      bellmanFord(
          5,
          {
              {0, 1, 6},
              {0, 2, 7},
              {1, 2, 8},
              {1, 3, 5},
              {1, 4, -4},
              {2, 3, -3},
              {2, 4, 9},
              {3, 1, -2},
              {4, 3, 7},
          },
          0),
      {0, 2, 7, 4, -2},
      "classic negative edge graph");

  // Reachable negative cycle.
  checkThrows(
      3,
      {
          {0, 1, 1},
          {1, 2, -2},
          {2, 1, -2},
      },
      0,
      "reachable negative cycle");

  // Negative self-loop reachable from source.
  checkThrows(
      2,
      {
          {0, 1, 5},
          {1, 1, -1},
      },
      0,
      "reachable negative self loop");

  // Unreachable negative cycle should NOT throw.
  {
    const long long INF = LLONG_MAX;

    check(
        bellmanFord(
            4,
            {
                {0, 1, 2},
                {2, 3, -5},
                {3, 2, -5},
            },
            0),
        {0, 2, INF, INF},
        "unreachable negative cycle ignored");
  }

  // Positive cycle is harmless.
  check(
      bellmanFord(
          3,
          {
              {0, 1, 2},
              {1, 2, 3},
              {2, 1, 1},
          },
          0),
      {0, 2, 5},
      "positive cycle");

  // Parallel edges.
  check(
      bellmanFord(
          3,
          {
              {0, 1, 10},
              {0, 1, 3},
              {1, 2, 4},
          },
          0),
      {0, 3, 7},
      "parallel edges choose cheaper one");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}