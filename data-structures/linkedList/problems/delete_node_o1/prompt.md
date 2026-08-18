# Delete Node in O(1)

Implement `deleteNode` for a singly linked list when the caller gives you a pointer to the node that should be deleted, but not the list head.

```cpp
void deleteNode(ListNode* node);
```

The target node is guaranteed to be in a list and is not the final node. Delete it in O(1) time by rearranging the node contents and links. The list owner remains responsible for deleting the final detached node and all remaining nodes.

## Requirements

- Make the successor's value occupy the target node and bypass the successor.
- Do not traverse from the head and do not allocate a replacement node.
- For `nullptr`, do nothing defensively.
- The function is not required to support deleting a tail node because it has no successor to copy.
