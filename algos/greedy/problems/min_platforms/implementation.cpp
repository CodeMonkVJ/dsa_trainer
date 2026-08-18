#include <bits/stdc++.h>
using namespace std;
int minPlatforms(const vector<int>& a,const vector<int>& d){vector<int>x=a,y=d;sort(x.begin(),x.end());sort(y.begin(),y.end());size_t i=0,j=0;int cur=0,best=0;while(i<x.size()){if(j==y.size()||x[i]<=y[j]){++cur;best=max(best,cur);++i;}else{--cur;++j;}}return best;}
int main(){cout<<minPlatforms({900,940,950,1100,1500,1800},{910,1200,1120,1130,1900,2000})<<'\n';return 0;}
