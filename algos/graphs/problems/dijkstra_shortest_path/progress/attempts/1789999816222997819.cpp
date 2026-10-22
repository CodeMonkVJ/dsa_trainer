#include <bits/stdc++.h>
#include <climits>
#include <queue>
#include <stdexcept>
#include <utility>
using namespace std;

using WeightedEdge = pair<int, int>;

const long long INF = numeric_limits<long long>::max() / 4;

static vector<long long> dijkstra(const vector<vector<WeightedEdge>> &edges,
                                  int source) {
  int vertices = edges.size();

  if (source < 0 || source >= vertices)
    throw invalid_argument("invalid source");

  for (const auto &adj : edges) {
    for (auto [neighbor, weight] : adj) {
      if (weight < 0)
        throw invalid_argument("negative edge weight");
    }
  }

  vector<long long> dist(vertices, INF);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      pq;

  pq.push({0, source});
  dist[source] = 0;

  while (!pq.empty()) {
    auto [distance, vertex] = pq.top();
    pq.pop();

    if (distance > dist[vertex])
      continue;

    for (auto [neighbor, edgeWeight] : edges[vertex]) {
      if (distance + edgeWeight < dist[neighbor]) {
        dist[neighbor] = edgeWeight + distance;
        pq.push(make_pair(dist[neighbor], neighbor));
      }
    }
  }

  return dist;
}
