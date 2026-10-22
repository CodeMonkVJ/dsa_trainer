#include <bits/stdc++.h>
#include <climits>
using namespace std;

struct Edge {
  int from, to;
  long long weight;
};

vector<long long> bellmanFord(int vertices, const vector<Edge> &edges,
                              int source) {
  if (source < 0 || source >= vertices)
    throw invalid_argument("invalid source");
  vector<long long> dist(vertices, LLONG_MAX);

  dist[source] = 0;

  for (int i = 0; i < vertices - 1; i++) {
    bool changed = false;

    for (auto edge : edges) {
      int u = edge.from;
      int v = edge.to;
      long long w = edge.weight;

      if (dist[u] != LLONG_MAX) {
        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          changed = true;
        }
      }
    }

    if (!changed)
      break;
  }

  for (auto edge : edges) {
    int u = edge.from;
    int v = edge.to;
    long long w = edge.weight;

    if (dist[u] != LLONG_MAX) {
      if (dist[u] + w < dist[v]) {
        throw runtime_error("reachable negative cycle");
      }
    }
  }

  return dist;
}
