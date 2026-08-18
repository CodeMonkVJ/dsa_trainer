#include <bits/stdc++.h>
using namespace std;
struct Node { int val; vector<Node*> neighbors; Node(int v):val(v){} };
Node* cloneGraph(Node* node) { if (!node) return nullptr; unordered_map<Node*,Node*> seen; queue<Node*> q; seen[node]=new Node(node->val); q.push(node); while(!q.empty()){Node* cur=q.front();q.pop(); for(Node* next:cur->neighbors){if(!seen.count(next)){seen[next]=new Node(next->val);q.push(next);} seen[cur]->neighbors.push_back(seen[next]);}} return seen[node]; }
