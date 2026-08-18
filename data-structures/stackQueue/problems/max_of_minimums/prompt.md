# Max of Minimums for Every Window Size

For each window size from `1` to `n`, compute the minimum value of every
window of that size and return the largest such minimum. The result at index
`k - 1` corresponds to window size `k`.

Implement:

```cpp
std::vector<int> maxOfMinimums(const std::vector<int>& values);
```

Return an empty vector for empty input. Aim for `O(n)` time using nearest
smaller-element boundaries.
