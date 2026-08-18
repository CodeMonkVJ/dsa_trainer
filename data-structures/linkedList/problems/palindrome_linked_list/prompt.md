# Palindrome Linked List

Implement `isPalindrome`, returning `true` when the values in a singly linked list are identical from both ends.

Use O(1) auxiliary space and O(n) time. It is acceptable to reverse part of the list, but restore the list before returning. Handle empty and one-node lists.

```cpp
struct ListNode { int value; ListNode* next; };
bool isPalindrome(ListNode* head);
ListNode* makeList(const std::vector<int>& values);
void freeList(ListNode* head);
```
