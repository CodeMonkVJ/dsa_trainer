#include <bits/stdc++.h>
using namespace std;

static void findPaths(const vector<vector<int>>& maze, vector<vector<bool>>& seen,
                      int row, int col, string& path, vector<string>& result) {
    const int n = static_cast<int>(maze.size());
    const int m = static_cast<int>(maze[0].size());
    if (row == n - 1 && col == m - 1) {
        result.push_back(path);
        return;
    }

    static const int dr[] = {1, 0, 0, -1};
    static const int dc[] = {0, -1, 1, 0};
    static const char move[] = {'D', 'L', 'R', 'U'};
    for (int i = 0; i < 4; ++i) {
        const int nextRow = row + dr[i];
        const int nextCol = col + dc[i];
        if (nextRow < 0 || nextRow >= n || nextCol < 0 || nextCol >= m ||
            seen[nextRow][nextCol] || maze[nextRow][nextCol] != 1) {
            continue;
        }
        seen[nextRow][nextCol] = true;
        path.push_back(move[i]);
        findPaths(maze, seen, nextRow, nextCol, path, result);
        path.pop_back();
        seen[nextRow][nextCol] = false;
    }
}

vector<string> ratInMaze(vector<vector<int>> maze) {
    if (maze.empty() || maze[0].empty()) return {};
    const size_t width = maze[0].size();
    for (const auto& row : maze) {
        if (row.size() != width) return {};
    }
    if (maze[0][0] != 1 || maze.back().back() != 1) return {};

    vector<vector<bool>> seen(maze.size(), vector<bool>(width, false));
    vector<string> result;
    string path;
    seen[0][0] = true;
    findPaths(maze, seen, 0, 0, path, result);
    sort(result.begin(), result.end());
    return result;
}

int main() {
    cout << ratInMaze({{1, 0}, {1, 1}}).size() << '\n';
    return 0;
}
