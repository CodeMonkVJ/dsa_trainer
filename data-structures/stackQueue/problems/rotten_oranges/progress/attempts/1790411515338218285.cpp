#include <bits/stdc++.h>
#include <utility>
using namespace std;

#define ROTTEN 2
#define FRESH 1
#define EMPTY 0

bool validCell(int n, int m, pair<int, int> cell) {
  if (cell.first < 0 || cell.first >= n)
    return false;
  if (cell.second < 0 || cell.second >= m)
    return false;
  return true;
}

int orangesRotting(vector<vector<int>> grid) {
  int minutes = 0;
  int freshCount = 0;

  int n = grid.size();
  if (n == 0)
    return 0;

  int m = grid[0].size();
  queue<pair<int, int>> q;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int cell = grid[i][j];
      if (cell == FRESH)
        freshCount++;
      if (cell == ROTTEN)
        q.push(make_pair(i, j));
    }
  }

  while (!q.empty()) {
    int sz = q.size();
    bool spread = false;
    while (sz--) {
      pair<int, int> cell = q.front();
      q.pop();

      vector<pair<int, int>> adjCells = {
          make_pair(cell.first, cell.second + 1),
          make_pair(cell.first + 1, cell.second),
          make_pair(cell.first - 1, cell.second),
          make_pair(cell.first, cell.second - 1)};

      for (auto adjCell : adjCells) {
        if (validCell(n, m, adjCell)) {
          int val = grid[adjCell.first][adjCell.second];
          if (val == FRESH) {
            grid[adjCell.first][adjCell.second] = ROTTEN;
            freshCount--;
            q.push(make_pair(adjCell.first, adjCell.second));
            spread = true;
          }
        }
      }
    }

    if (spread)
      minutes++;
  }

  if (freshCount > 0)
    return -1;

  return minutes;
}
