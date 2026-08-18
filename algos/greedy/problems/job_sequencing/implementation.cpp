#include <bits/stdc++.h>
using namespace std;
pair<int,int> jobScheduling(const vector<int>& d,const vector<int>& p){vector<pair<int,int>> a;int last=0;for(size_t i=0;i<d.size()&&i<p.size();++i)if(d[i]>0){a.push_back({p[i],d[i]});last=max(last,d[i]);}sort(a.rbegin(),a.rend());vector<char> used(last+1);int n=0,sum=0;for(auto [profit,deadline]:a)for(int s=min(deadline,last);s>=1;--s)if(!used[s]){used[s]=1;++n;sum+=profit;break;}return {n,sum};}
int main(){auto x=jobScheduling({2,1,2,1,3},{100,19,27,25,15});cout<<x.first<<' '<<x.second<<'\n';return 0;}
