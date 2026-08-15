/**
 * Dijkstra's Shortest Path
 *
 * Computes shortest distances from one source in a graph with non-negative
 * edge weights. The priority queue always expands the currently closest
 * unsettled vertex.
 *
 * Time: O((V + E) log V) with an adjacency list and binary heap
 * Extra space: O(V + E)
 *
 * Dijkstra is not valid when an edge can have a negative weight.
 */
#include <bits/stdc++.h>
using namespace std;

using WeightedEdge = pair<int, int>; // destination, weight
const long long INF = numeric_limits<long long>::max() / 4;

static vector<long long> dijkstra(
    const vector<vector<WeightedEdge>>& graph, int source) {
    vector<long long> distance(graph.size(), INF);
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pending;

    distance[source] = 0;
    pending.push({0, source});

    while (!pending.empty()) {
        auto [currentDistance, vertex] = pending.top();
        pending.pop();

        if (currentDistance != distance[vertex]) continue;

        for (auto [neighbor, weight] : graph[vertex]) {
            long long candidate = currentDistance + weight;
            if (candidate < distance[neighbor]) {
                distance[neighbor] = candidate;
                pending.push({candidate, neighbor});
            }
        }
    }
    return distance;
}

int main() {
    vector<vector<WeightedEdge>> graph(5);
    graph[0] = {{1, 4}, {2, 1}};
    graph[2] = {{1, 2}, {3, 5}};
    graph[1] = {{3, 1}};
    graph[3] = {{4, 3}};

    vector<long long> distances = dijkstra(graph, 0);
    for (int vertex = 0; vertex < static_cast<int>(distances.size()); ++vertex)
        cout << "0 -> " << vertex << ": " << distances[vertex] << '\n';
    return 0;
}
