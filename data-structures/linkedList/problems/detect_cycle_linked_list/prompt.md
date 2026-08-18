# Detect a Cycle in a Linked List

Given the head of a singly linked list, determine whether following `next` pointers eventually repeats a node. Return the first node that begins the cycle, or `nullptr` when the list is acyclic.

The cycle entry is the node reached when the loop begins, not merely any node inside the loop. Use O(1) auxiliary space, do not modify the links, and handle empty and one-node lists.

Implement:

```cpp
Node* detectCycle(Node* head);
```

Floyd's tortoise-and-hare method is sufficient: first detect a meeting point, then reset one pointer to the head and advance both one step at a time to locate the entry.
