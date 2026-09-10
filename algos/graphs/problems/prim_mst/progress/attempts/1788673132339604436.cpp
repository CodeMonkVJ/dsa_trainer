#include <bits/stdc++.h>
#include <queue>
using namespace std;

struct WeightedEdge {
  int to;
  long long weight;
};

struct Compare {
  bool operator()(const WeightedEdge &a, const WeightedEdge &b) const {
    return a.weight > b.weight;
  }
};

long long primMst(const vector<vector<WeightedEdge>> &adj) {
  int nodes = adj.size();
  if (nodes == 0)
    return 0;
  vector<int> visited(nodes);
  priority_queue<WeightedEdge, vector<WeightedEdge>, Compare> minHeap;

  for (auto x : adj[0])
    minHeap.push(x);

  visited[0] = 1;

  long long mstWeight = 0;
  int visitedCount = 1;

  while (!minHeap.empty()) {
    WeightedEdge cheapest = minHeap.top();
    minHeap.pop();
    if (visited[cheapest.to])
      continue;
    visited[cheapest.to] = 1;
    visitedCount++;
    mstWeight += cheapest.weight;
    for (auto x : adj[cheapest.to]) {
      if (!visited[x.to])
        minHeap.push(x);
    }
  }

  if (visitedCount != nodes)
    return -1;

  return mstWeight;
}
