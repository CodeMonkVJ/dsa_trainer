#include <bits/stdc++.h>
using namespace std;
int maxXorPair(const vector<int>& a){int ans=0;for(size_t i=0;i<a.size();++i)for(size_t j=i+1;j<a.size();++j)ans=max(ans,a[i]^a[j]);return ans;}
int main(){return 0;}

