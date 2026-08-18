#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };

long long maxWidth(TreeNode* root) {
    if (!root) return 0;
    unsigned long long answer = 0;
    queue<pair<TreeNode*, unsigned long long>> q;
    q.push({root, 0});
    while (!q.empty()) {
        const auto first = q.front().second;
        const size_t count = q.size();
        unsigned long long last = first;
        for (size_t i = 0; i < count; ++i) {
            auto [node, index] = q.front(); q.pop();
            index -= first;
            last = index;
            if (node->left) q.push({node->left, index * 2});
            if (node->right) q.push({node->right, index * 2 + 1});
        }
        answer = max(answer, last + 1);
    }
    return static_cast<long long>(answer);
}

int main() { TreeNode r(1); r.left = new TreeNode(3); r.right = new TreeNode(2); cout << maxWidth(&r) << '\n'; return 0; }
