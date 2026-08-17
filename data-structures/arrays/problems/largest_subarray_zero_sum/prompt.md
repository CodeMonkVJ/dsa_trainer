# Largest Subarray With Zero Sum

Implement:

```cpp
int longestZeroSumSubarray(const std::vector<int>& nums);
```

Return the maximum length of a contiguous subarray whose elements sum to zero.
Return `0` if no nonempty subarray qualifies. Use prefix sums and remember the
earliest index for each sum to achieve `O(n)` expected time.
