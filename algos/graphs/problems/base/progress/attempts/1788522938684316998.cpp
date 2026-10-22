#include <bits/stdc++.h>
#include <queue>
#include <stdexcept>
using namespace std;

static vector<int> topologicalSort(const vector<vector<int>> &adj) {
  int nodes = adj.size();

  queue<int> q;
  vector<int> indegree(nodes, 0);
  vector<int> topo;

  for (int i = 0; i < nodes; i++) {
    for (auto x : adj[i]) {
      indegree[x]++;
    }
  }

  for (int i = 0; i < nodes; i++) {
    if (indegree[i] == 0)
      q.push(i);
  }

  while (!q.empty()) {
    int el = q.front();
    q.pop();
    for (auto x : adj[el]) {
      indegree[x]--;
      if (indegree[x] == 0) {
        q.push(x);
      }
    }
    topo.push_back(el);
  }

  if (topo.size() != adj.size())
    return {};

  return topo;
}
