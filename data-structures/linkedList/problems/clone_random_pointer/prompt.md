# Clone Linked List With Random Pointer

Implement `copyRandomList` to return a deep copy of a list. Each node has `next` and `random`; `random` may be null or point to any node in the original list.

The clone must preserve values, order, and random relationships, share no nodes with the original, and run in O(n) time with O(1) auxiliary space (the interleaving technique). Do not modify the original list after returning.

```cpp
struct Node { int value; Node* next; Node* random; };
Node* copyRandomList(Node* head);
```
