# Search a 2D Matrix

Implement the following function:

```cpp
bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target);
```

The matrix is empty or has `m` rows and `n` columns. Every row is sorted in
ascending order, and the first value of each row is greater than the last value
of the previous row. Return `true` when `target` occurs and `false` otherwise.

Aim for `O(log(m * n))` time and `O(1)` extra space. Inputs have a consistent
number of columns when the matrix is non-empty.
