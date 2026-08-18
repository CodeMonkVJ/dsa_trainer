# Remove Nth Node From End

Implement `removeNthFromEnd` for a singly linked list.

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n);
```

The list stores one integer per node. Remove the node that is `n` positions from the end, where `n == 1` means the final node. Return the (possibly new) head.

## Requirements

- Return `nullptr` for an empty list.
- If `n` is positive and no larger than the list length, remove exactly one node.
- If `n <= 0` or `n` is larger than the list length, leave the list unchanged.
- Do not allocate replacement data nodes; the removed node must no longer be reachable from the returned list.
- Aim for O(length) time and O(1) auxiliary space.

The caller owns the nodes. The test harness frees the returned list after each case.
