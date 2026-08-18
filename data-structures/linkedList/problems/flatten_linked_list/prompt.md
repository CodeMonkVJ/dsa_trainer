# Flatten Linked List

Each node has `next` and `bottom` pointers. The `next` chain contains several sorted vertical lists, each linked through `bottom`. Implement `flatten` to merge all values into one sorted list connected only by `bottom`; every `next` pointer in the result must be null.

Use O(1) auxiliary node storage and do not allocate replacement data nodes. Return the original nodes. The input may be empty.

```cpp
struct Node { int value; Node* next; Node* bottom; };
Node* flatten(Node* head);
```
