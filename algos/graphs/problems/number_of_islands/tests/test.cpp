#include <bits/stdc++.h>
using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0, total = 0;

void check(const vector<vector<char>> &grid,
           int expected,
           const char *name) {
  ++total;

  int actual = numberOfIslands(grid);
  bool ok = (actual == expected);

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ")
       << name
       << " expected=" << expected
       << " actual=" << actual
       << '\n';
}

int main() {
  // Empty grid.
  check(
      {},
      0,
      "empty grid");

  // One water cell.
  check(
      {{'0'}},
      0,
      "single water cell");

  // One land cell.
  check(
      {{'1'}},
      1,
      "single land cell");

  // All water.
  check(
      {
          {'0', '0', '0'},
          {'0', '0', '0'}
      },
      0,
      "all water");

  // All land.
  check(
      {
          {'1', '1', '1'},
          {'1', '1', '1'}
      },
      1,
      "all land one island");

  // Two separate islands.
  check(
      {
          {'1', '1', '0', '0'},
          {'1', '0', '0', '1'},
          {'0', '0', '1', '1'},
          {'0', '0', '0', '0'}
      },
      2,
      "two islands");

  // Diagonal cells are NOT connected.
  check(
      {
          {'1', '0'},
          {'0', '1'}
      },
      2,
      "diagonal not connected");

  // Checkerboard.
  check(
      {
          {'1', '0', '1'},
          {'0', '1', '0'},
          {'1', '0', '1'}
      },
      5,
      "checkerboard islands");

  // Horizontal strip.
  check(
      {
          {'1', '1', '1', '1', '1'}
      },
      1,
      "single horizontal island");

  // Separated horizontal islands.
  check(
      {
          {'1', '1', '0', '1', '0', '1', '1'}
      },
      3,
      "multiple islands in one row");

  // Vertical strip.
  check(
      {
          {'1'},
          {'1'},
          {'1'},
          {'1'}
      },
      1,
      "single vertical island");

  // Separated vertical islands.
  check(
      {
          {'1'},
          {'0'},
          {'1'},
          {'0'},
          {'1'}
      },
      3,
      "multiple islands in one column");

  // Irregular connected shape.
  check(
      {
          {'1', '1', '0', '0'},
          {'0', '1', '0', '0'},
          {'0', '1', '1', '1'},
          {'0', '0', '0', '1'}
      },
      1,
      "irregular connected island");

  // Several components of different shapes.
  check(
      {
          {'1', '1', '0', '1', '0'},
          {'1', '0', '0', '1', '0'},
          {'0', '0', '1', '0', '0'},
          {'1', '0', '1', '1', '1'}
      },
      4,
      "multiple irregular islands");

  // Dense island with internal cycles in BFS traversal.
  // Useful for catching duplicate enqueues.
  check(
      {
          {'1', '1', '1'},
          {'1', '1', '1'},
          {'1', '1', '1'}
      },
      1,
      "dense land block");

  // Narrow winding island.
  check(
      {
          {'1', '1', '0', '0', '0'},
          {'0', '1', '0', '1', '1'},
          {'0', '1', '1', '1', '0'},
          {'0', '0', '0', '1', '0'}
      },
      1,
      "winding island");

  // Four isolated corners.
  check(
      {
          {'1', '0', '1'},
          {'0', '0', '0'},
          {'1', '0', '1'}
      },
      4,
      "isolated corners");

  // Large connected block with water border.
  check(
      {
          {'0', '0', '0', '0', '0'},
          {'0', '1', '1', '1', '0'},
          {'0', '1', '1', '1', '0'},
          {'0', '1', '1', '1', '0'},
          {'0', '0', '0', '0', '0'}
      },
      1,
      "land block surrounded by water");

  // Multiple islands where BFS moves far away
  // from the original outer-loop column.
  check(
      {
          {'1', '0', '0', '0', '1'},
          {'1', '1', '1', '0', '1'},
          {'0', '0', '1', '0', '1'},
          {'0', '0', '1', '1', '1'}
      },
      1,
      "bfs changes column while traversing");

  cout << "DSA_RESULT {\"passed\":"
       << passed
       << ",\"total\":"
       << total
       << "}\n";

  return passed == total ? 0 : 1;
}