#include <bits/stdc++.h>
using namespace std;
int stronglyConnectedComponents(const vector<vector<int>>& graph) { int n=graph.size();vector<bool>v(n);vector<int>order;function<void(int)>a=[&](int x){v[x]=true;for(int y:graph[x])if(!v[y])a(y);order.push_back(x);};for(int i=0;i<n;++i)if(!v[i])a(i);vector<vector<int>> rev(n);for(int i=0;i<n;++i)for(int j:graph[i])rev[j].push_back(i);fill(v.begin(),v.end(),false);int ans=0;function<void(int)>b=[&](int x){v[x]=true;for(int y:rev[x])if(!v[y])b(y);};for(auto it=order.rbegin();it!=order.rend();++it)if(!v[*it]){++ans;b(*it);}return ans; }

