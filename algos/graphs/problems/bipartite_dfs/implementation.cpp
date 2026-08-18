#include <bits/stdc++.h>
using namespace std;
bool isBipartiteDfs(const vector<vector<int>>& graph) { vector<int> c(graph.size(),-1);function<bool(int,int)>go=[&](int v,int col){c[v]=col;for(int n:graph[v]){if(c[n]<0&&!go(n,col^1))return false;if(c[n]==col)return false;}return true;};for(int i=0;i<static_cast<int>(graph.size());++i)if(c[i]<0&&!go(i,0))return false;return true; }

