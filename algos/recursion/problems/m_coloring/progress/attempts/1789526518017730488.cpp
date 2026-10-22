#include <bits/stdc++.h>
#include <vector>
using namespace std;

bool recurse(int i, vector<int> &coloured, const vector<vector<int>> &graph,
             int m) {

  if (i == coloured.size())
    return true;

  vector<int> neighbours;

  for (int j = 0; j < coloured.size(); j++) {
    if (graph[i][j] == 1)
      neighbours.push_back(j);
  }

  for (int c = 1; c <= m; c++) {
    bool safe = true;
    for (auto x : neighbours) {
      if (coloured[x] == c) {
        safe = false;
        break;
      }
    }
    if (safe) {
      coloured[i] = c;
      if (recurse(i + 1, coloured, graph, m)) {
        return true;
      }
      coloured[i] = 0;
    }
  }

  return false;
}

bool graphColoring(vector<vector<int>> graph, int m) {
  if (m <= 0)
    return false;

  int nodes = graph.size();

  if (nodes == 0)
    return true;

  int columns = graph[0].size();
  if (nodes != columns)
    return false;

  for (int i = 0; i < nodes; i++) {
    for (int j = 0; j < nodes; j++) {
      if (graph[i][j] > 1 || graph[i][j] < 0)
        return false;
      if (i == j && graph[i][j] == 1)
        return false;
    }
  }

  vector<int> coloured(nodes);

  return recurse(0, coloured, graph, m);
}
