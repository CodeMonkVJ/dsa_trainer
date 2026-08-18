# Merge Two Sorted Linked Lists

Implement `mergeTwoSortedLists`, which combines two singly linked lists sorted in non-decreasing order.

## Requirements

- Return the sorted merged list; either input may be `nullptr`.
- Reuse and relink the existing nodes. Do not allocate replacement list nodes.
- Preserve duplicate values and every input node exactly once.
- Run in O(n + m) time and O(1) auxiliary space.
- The input heads are no longer usable as separate lists after merging.
- Use `freeList` once on the returned list when you are finished with it.

The reference API is:

```cpp
struct ListNode { int value; ListNode* next; };
ListNode* mergeTwoSortedLists(ListNode* left, ListNode* right);
ListNode* makeList(const std::vector<int>& values);
void freeList(ListNode* head);
```
