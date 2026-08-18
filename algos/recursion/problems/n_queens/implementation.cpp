#include <bits/stdc++.h>
using namespace std;

static void place(int row, int n, vector<string>& board,
                  vector<bool>& columns, vector<bool>& downDiagonals,
                  vector<bool>& upDiagonals,
                  vector<vector<string>>& result) {
    if (row == n) {
        result.push_back(board);
        return;
    }

    for (int column = 0; column < n; ++column) {
        const int down = row - column + n - 1;
        const int up = row + column;
        if (columns[column] || downDiagonals[down] || upDiagonals[up]) {
            continue;
        }
        columns[column] = downDiagonals[down] = upDiagonals[up] = true;
        board[row][column] = 'Q';
        place(row + 1, n, board, columns, downDiagonals, upDiagonals, result);
        board[row][column] = '.';
        columns[column] = downDiagonals[down] = upDiagonals[up] = false;
    }
}

vector<vector<string>> nQueens(int n) {
    if (n <= 0) return {};
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    vector<bool> columns(n, false);
    vector<bool> downDiagonals(2 * n - 1, false);
    vector<bool> upDiagonals(2 * n - 1, false);
    place(0, n, board, columns, downDiagonals, upDiagonals, result);
    return result;
}

int main() {
    cout << nQueens(4).size() << '\n';
    return 0;
}
