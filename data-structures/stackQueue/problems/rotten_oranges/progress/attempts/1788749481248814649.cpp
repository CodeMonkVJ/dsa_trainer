#include <bits/stdc++.h>
#include <utility>
using namespace std;

bool isValid(pair<int, int> orange, int n, int m) {
  if (orange.first < 0 || orange.first >= n)
    return false;
  if (orange.second < 0 || orange.second >= m)
    return false;

  return true;
}

int orangesRotting(vector<vector<int>> grid) {
  int freshCount = 0;
  queue<pair<int, int>> rotten;
  int n = grid.size();
  if (n == 0)
    return 0;
  int m = grid[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int state = grid[i][j];
      if (state == 2)
        rotten.push(make_pair(i, j));
      else if (state == 1)
        freshCount++;
    }
  }

  if (freshCount == 0)
    return 0;

  int mins = -1;
  while (!rotten.empty()) {
    int levelSize = rotten.size();
    while (levelSize--) {
      pair<int, int> currRotten = rotten.front();
      rotten.pop();
      vector<pair<int, int>> adjOranges = {
          make_pair(currRotten.first - 1, currRotten.second),
          make_pair(currRotten.first, currRotten.second - 1),
          make_pair(currRotten.first + 1, currRotten.second),
          make_pair(currRotten.first, currRotten.second + 1),
      };
      for (auto x : adjOranges) {
        if (isValid(x, n, m)) {
          int state = grid[x.first][x.second];
          if (state == 1) {
            grid[x.first][x.second] = 2;
            freshCount--;
            rotten.push(x);
          }
        }
      }
    }
    mins++;
  }

  if (freshCount > 0)
    return -1;
  return mins;
}
