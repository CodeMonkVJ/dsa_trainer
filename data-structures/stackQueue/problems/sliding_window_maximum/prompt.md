# Sliding Window Maximum

Given an integer array and a window size `k`, return the maximum value for
each contiguous window from left to right. Return an empty vector when the
array is empty or `k` is not in the range `1..n`.

Implement:

```cpp
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k);
```

Aim for `O(n)` time using a deque of candidate indices.
