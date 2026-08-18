# Add Two Numbers

Implement `addTwoNumbers` for two non-negative integers represented by singly linked lists.

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
```

Each list stores one decimal digit per node in reverse order: the head contains the ones digit. Return a newly allocated list representing the sum in the same format.

## Requirements

- Support lists of different lengths and a final carry.
- Inputs may be empty; treat an empty list as zero.
- Do not mutate either input list.
- Return a single zero node when both inputs are empty or represent zero.
- Use O(max(m, n)) time and O(max(m, n)) output space.

The caller owns all three lists. The test harness frees the result and both inputs.
