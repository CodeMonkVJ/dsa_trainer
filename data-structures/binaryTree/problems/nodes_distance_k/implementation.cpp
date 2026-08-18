#include <bits/stdc++.h>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; TreeNode(int v): val(v), left(nullptr), right(nullptr) {} };

vector<int> nodesAtDistanceK(TreeNode* root, int target, int k) {
    if (!root || k < 0) return {};
    unordered_map<TreeNode*, TreeNode*> parent;
    TreeNode* wanted = nullptr;
    queue<TreeNode*> build; build.push(root); parent[root] = nullptr;
    while (!build.empty()) {
        TreeNode* node = build.front(); build.pop();
        if (node->val == target) wanted = node;
        if (node->left) parent[node->left] = node, build.push(node->left);
        if (node->right) parent[node->right] = node, build.push(node->right);
    }
    if (!wanted) return {};
    vector<int> answer; unordered_set<TreeNode*> seen; queue<pair<TreeNode*,int>> q;
    q.push({wanted,0}); seen.insert(wanted);
    while (!q.empty()) {
        auto [node, distance] = q.front(); q.pop();
        if (distance == k) { answer.push_back(node->val); continue; }
        for (TreeNode* next : {node->left, node->right, parent[node]})
            if (next && seen.insert(next).second) q.push({next, distance + 1});
    }
    return answer;
}

int main(){TreeNode r(3);r.left=new TreeNode(5);r.right=new TreeNode(1);cout<<nodesAtDistanceK(&r,3,1).size()<<'\n';return 0;}
