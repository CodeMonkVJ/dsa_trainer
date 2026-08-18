/**
 * Topological Sort using Kahn's Algorithm
 *
 * Produces an ordering of a directed acyclic graph (DAG) in which every
 * edge u -> v places u before v. Vertices with zero incoming degree are
 * processed first.
 *
 * Time: O(V + E)
 * Extra space: O(V)
 *
 * If fewer than V vertices are produced, the graph contains a cycle and
 * no topological ordering exists.
 */
#include <bits/stdc++.h>
using namespace std;

static vector<int> topologicalSort(const vector<vector<int>>& graph) {
    vector<int> indegree(graph.size(), 0);
    for (const auto& edges : graph)
        for (int destination : edges) ++indegree[destination];

    queue<int> ready;
    for (int vertex = 0; vertex < static_cast<int>(graph.size()); ++vertex)
        if (indegree[vertex] == 0) ready.push(vertex);

    vector<int> order;
    while (!ready.empty()) {
        int vertex = ready.front();
        ready.pop();
        order.push_back(vertex);

        for (int destination : graph[vertex])
            if (--indegree[destination] == 0) ready.push(destination);
    }

    if (order.size() != graph.size())
        throw logic_error("graph contains a directed cycle");
    return order;
}

int main() {
    vector<vector<int>> graph(6);
    graph[5] = {2, 0};
    graph[4] = {0, 1};
    graph[2] = {3};
    graph[3] = {1};

    for (int vertex : topologicalSort(graph)) cout << vertex << ' ';
    cout << '\n';
    return 0;
}
