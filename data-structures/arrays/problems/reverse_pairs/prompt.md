# Reverse Pairs

Implement the following function:

```cpp
long long reversePairs(std::vector<int>& nums);
```

Count pairs of indices `(i, j)` with `i < j` and
`nums[i] > 2LL * nums[j]`. Return the count and leave `nums` sorted in
ascending order when the function returns. The input may be empty.

Use `O(n log n)` time and `O(n)` auxiliary space. Use 64-bit arithmetic for
both the comparison and the answer.
