#include <bits/stdc++.h>
using namespace std;

int orangesRotting(vector<vector<int>> grid) {
  int rows = (int)grid.size();
  if (rows == 0) return 0;
  int cols = (int)grid[0].size();
  if (cols == 0) return 0;
  queue<pair<int, int>> rotten;
  int fresh = 0;
  for (int row = 0; row < rows; ++row) {
    if ((int)grid[row].size() != cols) return -1;
    for (int col = 0; col < cols; ++col) {
      if (grid[row][col] == 1) ++fresh;
      else if (grid[row][col] == 2) rotten.push({row, col});
    }
  }
  int minutes = 0;
  const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  while (!rotten.empty() && fresh > 0) {
    int level_size = (int)rotten.size();
    while (level_size-- > 0) {
      auto [row, col] = rotten.front();
      rotten.pop();
      for (const auto& direction : directions) {
        int next_row = row + direction[0];
        int next_col = col + direction[1];
        if (next_row < 0 || next_row >= rows || next_col < 0 || next_col >= cols || grid[next_row][next_col] != 1) continue;
        grid[next_row][next_col] = 2;
        --fresh;
        rotten.push({next_row, next_col});
      }
    }
    ++minutes;
  }
  return fresh == 0 ? minutes : -1;
}

int main() {
  cout << orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}) << '\n';
  return 0;
}
