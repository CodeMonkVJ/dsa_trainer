# Reverse Linked List

Implement `reverseList`, which reverses a singly linked list in place and returns the new head.

## Requirements

- Return `nullptr` for an empty list.
- Reverse the existing links; do not allocate replacement nodes.
- Preserve every node and value exactly once.
- Use O(1) auxiliary space and O(n) time.
- Use `freeList` to release a list created by the helper `makeList` when you are finished with it.

The reference API is:

```cpp
struct ListNode { int value; ListNode* next; };
ListNode* reverseList(ListNode* head);
ListNode* makeList(const std::vector<int>& values);
void freeList(ListNode* head);
```
