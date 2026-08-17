# Grid Unique Paths

Implement the following function:

```cpp
long long uniquePaths(int rows, int columns);
```

Count paths from `(0, 0)` to `(rows - 1, columns - 1)` in a grid. From each
cell, movement is allowed only right or down. `rows` and `columns` are positive
and small enough for the answer to fit in a signed 64-bit integer.

Return `0` for non-positive dimensions. Use `O(rows * columns)` time and at
most `O(columns)` extra space.
