/**
 * Undirected Graph with an Adjacency List
 *
 * Each vertex owns a vector of neighboring vertices.  BFS visits the
 * reachable component in O(V + E) time and uses O(V) auxiliary space.
 *
 * The graph is intentionally small and unweighted, which is the usual
 * starting point for interview graph traversal questions.
 */
#include <bits/stdc++.h>
using namespace std;

class Graph {
    vector<vector<int>> adjacency_;

    void validate(int vertex) const {
        if (vertex < 0 || vertex >= static_cast<int>(adjacency_.size()))
            throw out_of_range("graph vertex");
    }

public:
    explicit Graph(int vertices) : adjacency_(vertices) {
        if (vertices <= 0) throw invalid_argument("vertices must be positive");
    }

    void addEdge(int first, int second) {
        validate(first);
        validate(second);
        adjacency_[first].push_back(second);
        adjacency_[second].push_back(first);
    }

    vector<int> bfs(int start) const {
        validate(start);
        vector<bool> visited(adjacency_.size(), false);
        queue<int> pending;
        vector<int> order;
        pending.push(start);
        visited[start] = true;

        while (!pending.empty()) {
            int vertex = pending.front();
            pending.pop();
            order.push_back(vertex);
            for (int neighbor : adjacency_[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    pending.push(neighbor);
                }
            }
        }
        return order;
    }

    vector<int> dfs(int start) const {
        validate(start);
        vector<bool> visited(adjacency_.size(), false);
        vector<int> order;
        dfsFrom(start, visited, order);
        return order;
    }

private:
    void dfsFrom(int vertex, vector<bool>& visited, vector<int>& order) const {
        visited[vertex] = true;
        order.push_back(vertex);
        for (int neighbor : adjacency_[vertex])
            if (!visited[neighbor]) dfsFrom(neighbor, visited, order);
    }
};

void print(const vector<int>& values) {
    for (int value : values) cout << value << ' ';
    cout << '\n';
}

int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    cout << "BFS: "; print(graph.bfs(0));
    cout << "DFS: "; print(graph.dfs(0));
    return 0;
}
