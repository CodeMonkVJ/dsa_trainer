# Find Middle of Linked List

Implement `middleNode`, returning a pointer to the middle node of a singly linked list.

## Requirements

- Return `nullptr` for an empty list.
- For an even-length list, return the **second** of the two middle nodes.
- Traverse the list in O(n) time with O(1) auxiliary space.
- Do not modify links or allocate nodes.

The reference API is:

```cpp
struct ListNode { int value; ListNode* next; };
ListNode* middleNode(ListNode* head);
ListNode* makeList(const std::vector<int>& values);
void freeList(ListNode* head);
```
