#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };

TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
    if (preorder.size() != inorder.size() || preorder.empty()) return nullptr;
    unordered_map<int, int> at;
    for (int i = 0; i < (int)inorder.size(); ++i) at[inorder[i]] = i;
    function<TreeNode*(int,int,int,int)> make = [&](int pl, int pr, int il, int ir) -> TreeNode* {
        if (pl >= pr || il >= ir) return nullptr;
        auto it = at.find(preorder[pl]);
        if (it == at.end() || it->second < il || it->second >= ir) return nullptr;
        int mid = it->second, leftSize = mid - il;
        TreeNode* node = new TreeNode(preorder[pl]);
        node->left = make(pl + 1, pl + 1 + leftSize, il, mid);
        node->right = make(pl + 1 + leftSize, pr, mid + 1, ir);
        return node;
    };
    return make(0, (int)preorder.size(), 0, (int)inorder.size());
}
