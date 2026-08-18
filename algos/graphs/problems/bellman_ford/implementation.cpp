#include <bits/stdc++.h>
using namespace std;
struct Edge { int from,to; long long weight; }; vector<long long> bellmanFord(int n,const vector<Edge>& edges,int source) { const long long INF=LLONG_MAX/4;vector<long long>d(n,INF);d[source]=0;for(int i=1;i<n;++i){bool changed=false;for(auto e:edges)if(d[e.from]!=INF&&d[e.to]>d[e.from]+e.weight)d[e.to]=d[e.from]+e.weight,changed=true;if(!changed)break;}for(auto e:edges)if(d[e.from]!=INF&&d[e.to]>d[e.from]+e.weight)throw logic_error("negative cycle");return d; }

