# Bottom View of Binary Tree

Return the bottom view from left to right. At each horizontal distance, the deepest node wins; when depth ties, the later breadth-first node wins.

```cpp
struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<int> bottomView(TreeNode* root);
```
