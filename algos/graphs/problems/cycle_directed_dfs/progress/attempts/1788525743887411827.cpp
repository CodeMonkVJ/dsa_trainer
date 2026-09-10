#include <bits/stdc++.h>
using namespace std;

bool dfsHelper(const vector<vector<int>> &adj, int curr, vector<int> &status) {
  status[curr] = 1;
  for (auto x : adj[curr]) {
    if (status[x] == 1)
      return true;
    if (status[x] == 0) {
      status[x] = 1;
      if (dfsHelper(adj, x, status)) {
        return true;
      }
    }
  }

  status[curr] = 2;
  return false;
}

bool hasDirectedCycleDfs(const vector<vector<int>> &adj) {
  int nodes = adj.size();
  if (nodes == 0)
    return false;

  vector<int> status(nodes, 0);

  for (int i = 0; i < nodes; i++) {
    if (status[i] == 0) {
      if (dfsHelper(adj, i, status))
        return true;
    }
  }

  return false;
}
