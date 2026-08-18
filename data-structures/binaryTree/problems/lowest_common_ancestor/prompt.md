# Lowest Common Ancestor

Return the value of the lowest common ancestor of `first` and `second`. Return `nullopt` if either value is absent. Values are unique.

```cpp
struct TreeNode { int value; TreeNode* left; TreeNode* right; };
optional<int> lowestCommonAncestor(TreeNode* root, int first, int second);
```
