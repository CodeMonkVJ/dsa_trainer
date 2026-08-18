# N-Queens

Given a positive integer `n`, place `n` queens on an `n x n` chessboard so that no two queens share a row, column, or diagonal. Return every valid board configuration.

Represent each board as `n` strings of length `n`, using `Q` for a queen and `.` for an empty square. The order of the returned boards does not matter. For `n <= 0`, return an empty result.

Implement:

```cpp
std::vector<std::vector<std::string>> nQueens(int n);
```

Use backtracking and prune a placement when its column or either diagonal is already occupied.
