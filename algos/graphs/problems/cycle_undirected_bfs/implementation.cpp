#include <bits/stdc++.h>
using namespace std;
bool hasUndirectedCycleBfs(const vector<vector<int>>& graph) { vector<int> state(graph.size()); for(int s=0;s<static_cast<int>(graph.size());++s)if(!state[s]){queue<pair<int,int>>q;q.push({s,-1});state[s]=1;while(!q.empty()){auto [v,p]=q.front();q.pop();for(int n:graph[v]){if(n==p)continue;if(state[n])return true;state[n]=1;q.push({n,v});}}}return false; }

