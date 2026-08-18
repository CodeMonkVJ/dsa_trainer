#include <bits/stdc++.h>
using namespace std;
double fractionalKnapsack(const vector<int>& v,const vector<int>& w,int c){vector<pair<double,int>> a;for(size_t i=0;i<v.size()&&i<w.size();++i)if(w[i]>0&&v[i]>0)a.push_back({double(v[i])/w[i],w[i]});sort(a.rbegin(),a.rend());double ans=0;for(auto [density,weight]:a){int take=min(c,weight);ans+=density*take;c-=take;if(!c)break;}return ans;}
int main(){cout<<fractionalKnapsack({100,60,120},{20,10,30},50)<<'\n';return 0;}
