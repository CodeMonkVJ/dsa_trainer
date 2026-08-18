#include <bits/stdc++.h>
using namespace std;
bool isBipartiteBfs(const vector<vector<int>>& graph) { vector<int> color(graph.size(),-1);for(int s=0;s<static_cast<int>(graph.size());++s)if(color[s]<0){queue<int>q;q.push(s);color[s]=0;while(!q.empty()){int v=q.front();q.pop();for(int n:graph[v]){if(color[n]<0)color[n]=color[v]^1,q.push(n);else if(color[n]==color[v])return false;}}}return true; }

