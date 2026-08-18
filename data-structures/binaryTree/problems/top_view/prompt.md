# Top View of Binary Tree

Return the top view from left to right. At each horizontal distance, keep the first node encountered in breadth-first, top-to-bottom order.

```cpp
struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<int> topView(TreeNode* root);
```
