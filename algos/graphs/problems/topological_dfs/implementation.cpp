#include <bits/stdc++.h>
using namespace std;
vector<int> topologicalSortDfs(const vector<vector<int>>& graph) { vector<int> c(graph.size()),r;function<void(int)>go=[&](int v){c[v]=1;for(int n:graph[v]){if(c[n]==1)throw logic_error("cycle");if(!c[n])go(n);}c[v]=2;r.push_back(v);};for(int i=0;i<static_cast<int>(graph.size());++i)if(!c[i])go(i);reverse(r.begin(),r.end());return r; }

