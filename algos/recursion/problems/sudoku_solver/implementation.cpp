#include <bits/stdc++.h>
using namespace std;

static bool validShape(const vector<vector<char>>& b) {
    if (b.size() != 9) return false;
    for (const auto& row : b) if (row.size() != 9) return false;
    return true;
}

static bool solve(vector<vector<char>>& b, array<int, 9>& rows,
                  array<int, 9>& cols, array<int, 9>& boxes) {
    int bestR = -1, bestC = -1, bestMask = 0, bestCount = 10;
    for (int r = 0; r < 9; ++r) for (int c = 0; c < 9; ++c) {
        if (b[r][c] != '.') continue;
        int used = rows[r] | cols[c] | boxes[(r / 3) * 3 + c / 3];
        int mask = (~used) & 0x1FF, count = __builtin_popcount((unsigned)mask);
        if (count == 0) return false;
        if (count < bestCount) { bestCount = count; bestR = r; bestC = c; bestMask = mask; }
    }
    if (bestR == -1) return true;
    int box = (bestR / 3) * 3 + bestC / 3;
    while (bestMask) {
        int bit = bestMask & -bestMask;
        bestMask -= bit;
        b[bestR][bestC] = char('1' + __builtin_ctz((unsigned)bit));
        rows[bestR] |= bit; cols[bestC] |= bit; boxes[box] |= bit;
        if (solve(b, rows, cols, boxes)) return true;
        rows[bestR] ^= bit; cols[bestC] ^= bit; boxes[box] ^= bit;
        b[bestR][bestC] = '.';
    }
    return false;
}

bool solveSudoku(vector<vector<char>>& board) {
    if (!validShape(board)) return false;
    array<int, 9> rows{}, cols{}, boxes{};
    for (int r = 0; r < 9; ++r) for (int c = 0; c < 9; ++c) {
        char ch = board[r][c];
        if (ch == '.') continue;
        if (ch < '1' || ch > '9') return false;
        int bit = 1 << (ch - '1'), box = (r / 3) * 3 + c / 3;
        if ((rows[r] | cols[c] | boxes[box]) & bit) return false;
        rows[r] |= bit; cols[c] |= bit; boxes[box] |= bit;
    }
    return solve(board, rows, cols, boxes);
}

int main() {
    vector<vector<char>> board(9, vector<char>(9, '.'));
    cout << solveSudoku(board) << '\n';
    return 0;
}
