# Four Sum

Implement:

```cpp
std::vector<std::array<int, 4>> fourSum(std::vector<int> nums, long long target);
```

Return every unique quadruplet of values adding to `target`. Each quadruplet
must be nondecreasing, and the result must be sorted lexicographically. Do not
reuse an index. Return an empty vector when no answer exists.

Aim for `O(n^3)` time after sorting and `O(1)` extra space apart from the result.
