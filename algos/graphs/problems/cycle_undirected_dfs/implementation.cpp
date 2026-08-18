#include <bits/stdc++.h>
using namespace std;
bool hasUndirectedCycleDfs(const vector<vector<int>>& graph) { vector<bool> seen(graph.size()); function<bool(int,int)> go=[&](int v,int p){seen[v]=true;for(int n:graph[v]){if(!seen[n]){if(go(n,v))return true;}else if(n!=p)return true;}return false;};for(int i=0;i<static_cast<int>(graph.size());++i)if(!seen[i]&&go(i,-1))return true;return false; }

