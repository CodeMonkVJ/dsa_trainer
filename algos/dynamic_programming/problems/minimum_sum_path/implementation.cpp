#include <bits/stdc++.h>
using namespace std;

int minPathSum(const vector<vector<int>>& grid) {
    if (grid.empty() || grid.front().empty()) throw invalid_argument("grid cannot be empty");
    const int rows = static_cast<int>(grid.size());
    const int columns = static_cast<int>(grid.front().size());
    vector<int> dp(columns, INT_MAX);
    dp[0] = 0;
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            if (row == 0 && column == 0) dp[column] = grid[row][column];
            else dp[column] = grid[row][column] + min(dp[column], column ? dp[column - 1] : INT_MAX);
        }
    }
    return dp.back();
}

int main() { return 0; }

