# Celebrity Problem

Given an `n x n` matrix, `knows[i][j]` is non-zero when person `i` knows
person `j`. A celebrity is known by every other person and knows nobody else.
Return the celebrity's zero-based index, or `-1` when there is no celebrity.

Implement:

```cpp
int findCelebrity(const std::vector<std::vector<int>>& knows);
```

The matrix is square. Aim for `O(n)` relationship checks and `O(1)` extra
space; the input matrix itself does not count as extra space.
