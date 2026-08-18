#include <bits/stdc++.h>
using namespace std;
int maxSumIncreasing(const vector<int>& a){vector<int>d=a;int ans=0;for(size_t i=0;i<a.size();++i){for(size_t j=0;j<i;++j)if(a[j]<a[i])d[i]=max(d[i],d[j]+a[i]);ans=max(ans,d[i]);}return ans;}
int main(){return 0;}

