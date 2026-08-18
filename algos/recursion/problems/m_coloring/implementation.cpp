#include <bits/stdc++.h>
using namespace std;

static bool colorVertex(const vector<vector<int>>& g, int m, vector<int>& color, int v) {
    if (v == (int)g.size()) return true;
    for (int candidate = 1; candidate <= m; ++candidate) {
        bool allowed = true;
        for (int u = 0; u < (int)g.size(); ++u)
            if (g[v][u] && color[u] == candidate) { allowed = false; break; }
        if (!allowed) continue;
        color[v] = candidate;
        if (colorVertex(g, m, color, v + 1)) return true;
        color[v] = 0;
    }
    return false;
}

bool graphColoring(vector<vector<int>> graph, int m) {
    int n = (int)graph.size();
    if (m <= 0) return n == 0;
    for (const auto& row : graph) if ((int)row.size() != n) return false;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
        if (graph[i][j] < 0 || graph[i][j] > 1 || (i == j && graph[i][j])) return false;
    vector<int> color(n);
    return colorVertex(graph, m, color, 0);
}

int main() { cout << graphColoring({{0, 1}, {1, 0}}, 2) << '\n'; return 0; }
