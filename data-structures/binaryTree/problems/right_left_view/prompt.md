# Right and Left View of Binary Tree

Return the first visible node at every depth from the left and right sides.

```cpp
struct TreeNode { int value; TreeNode* left; TreeNode* right; };
vector<int> leftView(TreeNode* root);
vector<int> rightView(TreeNode* root);
```
