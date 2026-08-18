# Reverse Nodes in K-Group

Given the head of a singly linked list and an integer `k`, reverse nodes in each contiguous group of exactly `k` nodes. If fewer than `k` nodes remain at the end, leave that final group in its original order. Return the new head.

Perform the transformation in place by changing links; do not allocate replacement list nodes. Treat `k <= 1` as a no-op. Aim for O(n) time and O(1) auxiliary space.

Implement:

```cpp
Node* reverseKGroup(Node* head, int k);
```

For example, `[1,2,3,4,5]` with `k = 2` becomes `[2,1,4,3,5]`.
