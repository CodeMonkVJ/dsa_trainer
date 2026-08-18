# Rotate Linked List

Implement:

```cpp
ListNode* rotateRight(ListNode* head, int k);
```

Move the last `k` nodes of a singly linked list to the front and return the
new head. The rotation is to the right, so rotating `[1, 2, 3, 4, 5]` by `2`
produces `[4, 5, 1, 2, 3]`. Handle an empty list, a one-node list, zero or
negative `k`, and values of `k` larger than the list length. Re-link existing
nodes in `O(n)` time and `O(1)` auxiliary space.
