# Count Subarrays With Given XOR

Implement:

```cpp
long long countSubarraysWithXor(const std::vector<int>& nums, int target);
```

Return the number of nonempty contiguous subarrays whose bitwise XOR is
`target`. Count each pair of endpoints separately. Return `0` for an empty
input. Aim for `O(n)` expected time and `O(n)` extra space.
