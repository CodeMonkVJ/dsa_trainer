#include <bits/stdc++.h>
using namespace std;

#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(bool actual, bool expected, const char *input, const char *name) {
  ++total;

  bool ok = actual == expected;

  if (ok)
    ++passed;

  dsa_test::emit_case(
      input,
      expected ? "true" : "false",
      actual ? "true" : "false",
      ok);

  cout << (ok ? "PASS " : "FAIL ")
       << name << '\n';
}

int main() {
  // Empty graph.
  check(
      graphColoring({}, 1),
      true,
      R"({"graph":[],"colors":1})",
      "empty graph with valid color count");

  check(
      graphColoring({}, 0),
      false,
      R"({"graph":[],"colors":0})",
      "reject zero colors");

  check(
      graphColoring({}, -1),
      false,
      R"({"graph":[],"colors":-1})",
      "reject negative colors");

  // Single vertex.
  check(
      graphColoring({{0}}, 1),
      true,
      R"({"graph":[[0]],"colors":1})",
      "single isolated vertex");

  check(
      graphColoring({{0}}, 2),
      true,
      R"({"graph":[[0]],"colors":2})",
      "single vertex with extra colors");

  check(
      graphColoring({{1}}, 2),
      false,
      R"({"graph":[[1]],"colors":2})",
      "reject self loop");

  // Basic path.
  check(
      graphColoring(
          {
              {0, 1, 0},
              {1, 0, 1},
              {0, 1, 0},
          },
          2),
      true,
      R"({"graph":[[0,1,0],[1,0,1],[0,1,0]],"colors":2})",
      "path is two colorable");

  // Triangle.
  check(
      graphColoring(
          {
              {0, 1, 1},
              {1, 0, 1},
              {1, 1, 0},
          },
          2),
      false,
      R"({"graph":[[0,1,1],[1,0,1],[1,1,0]],"colors":2})",
      "triangle not two colorable");

  check(
      graphColoring(
          {
              {0, 1, 1},
              {1, 0, 1},
              {1, 1, 0},
          },
          3),
      true,
      R"({"graph":[[0,1,1],[1,0,1],[1,1,0]],"colors":3})",
      "triangle is three colorable");

  // Even cycle.
  check(
      graphColoring(
          {
              {0, 1, 0, 1},
              {1, 0, 1, 0},
              {0, 1, 0, 1},
              {1, 0, 1, 0},
          },
          2),
      true,
      R"({"graph":[[0,1,0,1],[1,0,1,0],[0,1,0,1],[1,0,1,0]],"colors":2})",
      "even cycle is two colorable");

  // Odd cycle.
  check(
      graphColoring(
          {
              {0, 1, 0, 0, 1},
              {1, 0, 1, 0, 0},
              {0, 1, 0, 1, 0},
              {0, 0, 1, 0, 1},
              {1, 0, 0, 1, 0},
          },
          2),
      false,
      R"({"graph":[[0,1,0,0,1],[1,0,1,0,0],[0,1,0,1,0],[0,0,1,0,1],[1,0,0,1,0]],"colors":2})",
      "odd cycle not two colorable");

  check(
      graphColoring(
          {
              {0, 1, 0, 0, 1},
              {1, 0, 1, 0, 0},
              {0, 1, 0, 1, 0},
              {0, 0, 1, 0, 1},
              {1, 0, 0, 1, 0},
          },
          3),
      true,
      R"({"graph":[[0,1,0,0,1],[1,0,1,0,0],[0,1,0,1,0],[0,0,1,0,1],[1,0,0,1,0]],"colors":3})",
      "odd cycle is three colorable");

  // Complete graph K4.
  check(
      graphColoring(
          {
              {0, 1, 1, 1},
              {1, 0, 1, 1},
              {1, 1, 0, 1},
              {1, 1, 1, 0},
          },
          3),
      false,
      R"({"graph":[[0,1,1,1],[1,0,1,1],[1,1,0,1],[1,1,1,0]],"colors":3})",
      "K4 needs four colors");

  check(
      graphColoring(
          {
              {0, 1, 1, 1},
              {1, 0, 1, 1},
              {1, 1, 0, 1},
              {1, 1, 1, 0},
          },
          4),
      true,
      R"({"graph":[[0,1,1,1],[1,0,1,1],[1,1,0,1],[1,1,1,0]],"colors":4})",
      "K4 with four colors");

  // No edges.
  check(
      graphColoring(
          {
              {0, 0, 0, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0},
              {0, 0, 0, 0},
          },
          1),
      true,
      R"({"graph":[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]],"colors":1})",
      "edgeless graph needs one color");

  // Any graph with an edge cannot use one color.
  check(
      graphColoring(
          {
              {0, 1},
              {1, 0},
          },
          1),
      false,
      R"({"graph":[[0,1],[1,0]],"colors":1})",
      "single edge not one colorable");

  // Disconnected components.
  check(
      graphColoring(
          {
              {0, 1, 0, 0, 0},
              {1, 0, 0, 0, 0},
              {0, 0, 0, 1, 1},
              {0, 0, 1, 0, 1},
              {0, 0, 1, 1, 0},
          },
          2),
      false,
      R"({"graph":[[0,1,0,0,0],[1,0,0,0,0],[0,0,0,1,1],[0,0,1,0,1],[0,0,1,1,0]],"colors":2})",
      "disconnected graph with triangle component");

  check(
      graphColoring(
          {
              {0, 1, 0, 0, 0},
              {1, 0, 0, 0, 0},
              {0, 0, 0, 1, 1},
              {0, 0, 1, 0, 1},
              {0, 0, 1, 1, 0},
          },
          3),
      true,
      R"({"graph":[[0,1,0,0,0],[1,0,0,0,0],[0,0,0,1,1],[0,0,1,0,1],[0,0,1,1,0]],"colors":3})",
      "disconnected graph with enough colors");

  // Non-square matrices.
  check(
      graphColoring(
          {
              {0, 1},
              {1},
          },
          2),
      false,
      R"({"graph":[[0,1],[1]],"colors":2})",
      "reject ragged matrix");

  check(
      graphColoring(
          {
              {0, 1, 0},
              {1, 0, 1},
          },
          2),
      false,
      R"({"graph":[[0,1,0],[1,0,1]],"colors":2})",
      "reject rectangular non square matrix");

  // Invalid entries.
  check(
      graphColoring(
          {
              {0, 2},
              {2, 0},
          },
          2),
      false,
      R"({"graph":[[0,2],[2,0]],"colors":2})",
      "reject entry greater than one");

  check(
      graphColoring(
          {
              {0, -1},
              {-1, 0},
          },
          2),
      false,
      R"({"graph":[[0,-1],[-1,0]],"colors":2})",
      "reject negative adjacency entry");

  // A slightly more involved graph.
  //
  // 0 -- 1
  // | \  |
  // |  \ |
  // 3 -- 2 -- 4
  //
  // Contains triangle 0-1-2, so 2 colors fail.
  check(
      graphColoring(
          {
              {0, 1, 1, 1, 0},
              {1, 0, 1, 0, 0},
              {1, 1, 0, 1, 1},
              {1, 0, 1, 0, 0},
              {0, 0, 1, 0, 0},
          },
          2),
      false,
      R"({"graph":[[0,1,1,1,0],[1,0,1,0,0],[1,1,0,1,1],[1,0,1,0,0],[0,0,1,0,0]],"colors":2})",
      "complex graph fails with two colors");

  check(
      graphColoring(
          {
              {0, 1, 1, 1, 0},
              {1, 0, 1, 0, 0},
              {1, 1, 0, 1, 1},
              {1, 0, 1, 0, 0},
              {0, 0, 1, 0, 0},
          },
          3),
      true,
      R"({"graph":[[0,1,1,1,0],[1,0,1,0,0],[1,1,0,1,1],[1,0,1,0,0],[0,0,1,0,0]],"colors":3})",
      "complex graph succeeds with three colors");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}