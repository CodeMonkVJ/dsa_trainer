#include <bits/stdc++.h>
using namespace std;
bool hasDirectedCycleBfs(const vector<vector<int>>& graph) { vector<int> in(graph.size());for(auto&e:graph)for(int n:e)++in[n];queue<int>q;for(int i=0;i<static_cast<int>(graph.size());++i)if(!in[i])q.push(i);int seen=0;while(!q.empty()){int v=q.front();q.pop();++seen;for(int n:graph[v])if(--in[n]==0)q.push(n);}return seen!=static_cast<int>(graph.size()); }

