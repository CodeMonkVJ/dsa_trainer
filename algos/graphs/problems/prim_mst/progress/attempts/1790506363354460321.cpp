#include <bits/stdc++.h>
using namespace std;

struct WeightedEdge {
  int to;
  long long weight;
};

// weight, to
#define entry pair<long long, int>

void pushAllEdges(priority_queue<entry, vector<entry>, greater<entry>> &minHeap,
                  const vector<WeightedEdge> &edges) {
  for (auto edge : edges) {
    auto [dest, weight] = edge;
    minHeap.push(make_pair(weight, dest));
  }
}

long long primMst(const vector<vector<WeightedEdge>> &adjList) {
  if (adjList.empty())
    return 0;

  long long ans = 0;
  int nodes = adjList.size();
  unordered_set<int> inMST;
  priority_queue<entry, vector<entry>, greater<entry>> minHeap;

  int source = 0;
  inMST.insert(source);

  pushAllEdges(minHeap, adjList[source]);

  while (!minHeap.empty()) {
    auto [weight, dest] = minHeap.top();
    minHeap.pop();
    if (inMST.count(dest) == 0) {
      inMST.insert(dest);
      ans += weight;
      pushAllEdges(minHeap, adjList[dest]);
    }
  }

  if (inMST.size() != nodes)
    return -1;

  return ans;
}
