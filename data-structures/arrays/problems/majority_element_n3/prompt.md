# Majority Elements (n/3)

Implement the following function:

```cpp
std::vector<int> majorityElements(const std::vector<int>& nums);
```

Return every distinct value occurring strictly more than `nums.size() / 3`
times. Return the result in ascending order. The input may be empty.

Use `O(n)` time and `O(1)` auxiliary space apart from the returned vector. Do
not reorder the input; a final verification pass is required because a
candidate is not automatically a majority.
