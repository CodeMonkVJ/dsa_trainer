#include <bits/stdc++.h>
using namespace std;
struct WeightedEdge { int to; long long weight; }; long long primMst(const vector<vector<WeightedEdge>>&g) { if(g.empty())return 0;vector<bool>v(g.size());priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>q;q.push({0,0});long long ans=0;int seen=0;while(!q.empty()){auto [w,x]=q.top();q.pop();if(v[x])continue;v[x]=true;++seen;ans+=w;for(auto e:g[x])if(!v[e.to])q.push({e.weight,e.to});}if(seen!=static_cast<int>(g.size()))throw logic_error("disconnected graph");return ans; }

