#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const vector<vector<int>> &graph,
           bool expected,
           const char *name) {
  ++total;

  bool actual = hasDirectedCycleDfs(graph);
  bool ok = actual == expected;

  if (ok)
    ++passed;

  cout << "DSA_CASE {\"input\":{\"graph\":[";
  for (size_t i = 0; i < graph.size(); ++i) {
    if (i)
      cout << ',';

    cout << '[';
    for (size_t j = 0; j < graph[i].size(); ++j) {
      if (j)
        cout << ',';
      cout << graph[i][j];
    }
    cout << ']';
  }

  cout << "]},\"expected\":" << (expected ? "true" : "false")
       << ",\"actual\":" << (actual ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  check({},
        false,
        "empty graph");

  check({{}},
        false,
        "single isolated vertex");

  check({{0}},
        true,
        "self loop");

  check({{1}, {2}, {}},
        false,
        "simple acyclic chain");

  check({{1}, {2}, {0}},
        true,
        "simple directed cycle");

  check({{1, 2}, {3}, {3}, {}},
        false,
        "diamond DAG");

  check({{1, 2}, {}, {3}, {1}},
        false,
        "cross edge to completed vertex is not a cycle");

  check({{1}, {}, {3}, {2}},
        true,
        "cycle in disconnected component");

  check({{1, 2}, {3}, {}, {4}, {1}},
        true,
        "long back edge cycle");

  check({{1, 2, 3}, {}, {}, {}},
        false,
        "multiple outgoing neighbours");

  check({{1}, {2}, {3}, {4}, {}},
        false,
        "long acyclic chain");

  check({{1}, {2}, {3}, {1}},
        true,
        "cycle not involving start vertex");

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}