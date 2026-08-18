# Intersection of Two Linked Lists

Given the heads of two singly linked lists, return the first node that is shared by both lists. The lists may merge into a Y-shaped structure: after the shared node, both lists follow the exact same nodes. Return `nullptr` when they do not intersect.

The comparison is by node identity, not by node value. Do not allocate replacement nodes and do not modify either list. Aim for O(n + m) time and O(1) auxiliary space.

Implement:

```cpp
Node* getIntersectionNode(Node* headA, Node* headB);
```

The returned pointer must be the actual shared node. An empty list, two disjoint lists, or either null head produces `nullptr`.
