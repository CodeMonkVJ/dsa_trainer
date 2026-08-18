#include <bits/stdc++.h>
using namespace std;
bool hasDirectedCycleDfs(const vector<vector<int>>& graph) { vector<int> color(graph.size()); function<bool(int)> go=[&](int v){color[v]=1;for(int n:graph[v]){if(color[n]==1)return true;if(color[n]==0&&go(n))return true;}color[v]=2;return false;};for(int i=0;i<static_cast<int>(graph.size());++i)if(!color[i]&&go(i))return true;return false; }

