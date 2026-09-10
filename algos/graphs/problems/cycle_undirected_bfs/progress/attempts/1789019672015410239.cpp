#include <bits/stdc++.h>
#include <utility>
using namespace std;

bool bfsCycleDetect(pair<int, int> node, const vector<vector<int>> &graph,
                    vector<int> &visited) {
  queue<pair<int, int>> q;
  q.push(node);
  visited[node.first] = 1;

  while (!q.empty()) {
    int curr = q.front().first;
    int parent = q.front().second;
    q.pop();
    for (auto neighbor : graph[curr]) {
      if (!visited[neighbor]) {
        visited[neighbor] = 1;
        q.push(make_pair(neighbor, curr));
      } else if (visited[neighbor] && neighbor != parent) {
        return true;
      }
    }
  }

  return false;
}

bool hasUndirectedCycleBfs(const vector<vector<int>> &graph) {
  int n = graph.size();
  vector<int> visited(n);
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      if (bfsCycleDetect(make_pair(i, -1), graph, visited)) {
        return true;
      }
    }
  }
  return false;
}
