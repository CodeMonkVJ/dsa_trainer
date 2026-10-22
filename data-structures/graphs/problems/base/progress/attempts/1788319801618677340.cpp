#include <bits/stdc++.h>
using namespace std;

class Graph {
  vector<vector<int>> adj;

public:
  explicit Graph(int vertices) : adj(vertices) {}
  void addEdge(int u, int v) {
    if (u < 0 || v < 0)
      throw out_of_range("invalid vertex");
    if (u >= adj.size() || v >= adj.size())
      throw out_of_range("invalid vertex");
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  vector<int> bfs(int start) const {
    if (start < 0 || start >= adj.size())
      throw out_of_range("invalid vertex");
    queue<int> q;
    vector<int> visited(adj.size());
    vector<int> traversal;
    q.push(start);
    visited[start] = 1;
    while (!q.empty()) {
      int curr = q.front();
      traversal.push_back(curr);
      for (auto x : adj[curr]) {
        if (!visited[x]) {
          visited[x] = 1;
          q.push(x);
        }
      }
      q.pop();
    }

    return traversal;
  }

  void dfsHelper(int current, vector<int> &visited,
                 vector<int> &traversal) const {
    if (!visited[current]) {
      traversal.push_back(current);
      visited[current] = 1;
    } else
      return;
    for (auto x : adj[current]) {
      dfsHelper(x, visited, traversal);
    }
  }
  vector<int> dfs(int start) const {
    if (start < 0 || start >= adj.size())
      throw out_of_range("invalid vertex");
    vector<int> visited(adj.size());
    vector<int> traversal;
    int current = start;
    dfsHelper(current, visited, traversal);
    return traversal;
  }
};
