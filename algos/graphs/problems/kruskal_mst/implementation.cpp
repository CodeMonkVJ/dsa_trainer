#include <bits/stdc++.h>
using namespace std;
struct Edge { int from,to; long long weight; }; long long kruskalMst(int n,vector<Edge> edges) { vector<int>p(n),sz(n,1);iota(p.begin(),p.end(),0);function<int(int)>find=[&](int x){return p[x]==x?x:p[x]=find(p[x]);};sort(edges.begin(),edges.end(),[](auto&a,auto&b){return a.weight<b.weight;});long long ans=0;int used=0;for(auto e:edges){int a=find(e.from),b=find(e.to);if(a==b)continue;if(sz[a]<sz[b])swap(a,b);p[b]=a;sz[a]+=sz[b];ans+=e.weight;++used;}if(used!=n-1)throw logic_error("disconnected graph");return ans; }

