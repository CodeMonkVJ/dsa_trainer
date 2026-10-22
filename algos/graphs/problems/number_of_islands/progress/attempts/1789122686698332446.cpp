#include <bits/stdc++.h>
#include <utility>
using namespace std;
int numberOfIslands(vector<vector<char>> grid) {
  int count = 0;
  int n = grid.size();
  if (n == 0)
    return 0;
  int m = grid[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '1') {
        count++;
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));
        while (!q.empty()) {
          pair<int, int> curr = q.front();
          int x = curr.first;
          int y = curr.second;
          q.pop();
          grid[x][y] = '0';
          if (x + 1 < n && x + 1 >= 0 && grid[x + 1][y] == '1') {
            q.push(make_pair(x + 1, y));
          }
          if (x - 1 < n && x - 1 >= 0 && grid[x - 1][y] == '1') {
            q.push(make_pair(x - 1, y));
          }
          if (y + 1 < m && y + 1 >= 0 && grid[x][y + 1] == '1') {
            q.push(make_pair(x, y + 1));
          }
          if (y - 1 < m && y - 1 >= 0 && grid[x][y - 1] == '1') {
            q.push(make_pair(x, y - 1));
          }
        }
      }
    }
  }

  return count;
}
