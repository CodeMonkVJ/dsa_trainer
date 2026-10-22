#include <bits/stdc++.h>
#include <queue>
#include <stdexcept>
#include <utility>
using namespace std;

// destinationVertex, edgeWeight
using WeightedEdge = pair<int, int>;

// distanceFromSource, destinationVertex
using Entry = pair<long long, int>;

const long long INF = numeric_limits<long long>::max() / 4;

static vector<long long> dijkstra(const vector<vector<WeightedEdge>> &adjList,
                                  int source) {
  int nodes = adjList.size();
  vector<long long> dist(nodes, INF);
  priority_queue<Entry, vector<Entry>, greater<Entry>> minHeap;

  if (nodes == 0)
    return {};

  if (source < 0 || source >= nodes)
    throw invalid_argument("invalid source");

  for (const auto &edges : adjList) {
    for (const auto &[destinationVertex, edgeWeight] : edges) {
      if (edgeWeight < 0)
        throw invalid_argument("negative edge weight");
    }
  }

  dist[source] = 0;
  minHeap.push(make_pair(0, source));

  while (!minHeap.empty()) {
    auto [distFromSource, vertex] = minHeap.top();
    minHeap.pop();
    if (distFromSource > dist[vertex])
      continue;
    else {
      for (auto &[destinationVertex, edgeWeight] : adjList[vertex]) {
        if (edgeWeight < 0)
          throw invalid_argument("negative edge");
        if (dist[destinationVertex] > dist[vertex] + edgeWeight) {
          dist[destinationVertex] = dist[vertex] + edgeWeight;
          minHeap.push(make_pair(dist[destinationVertex], destinationVertex));
        }
      }
    }
  }

  return dist;
}
