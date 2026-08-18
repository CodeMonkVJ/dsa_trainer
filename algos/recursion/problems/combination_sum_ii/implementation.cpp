#include <bits/stdc++.h>
using namespace std; void go(vector<int>&a,int i,int t,vector<int>&c,vector<vector<int>>&r){if(!t){r.push_back(c);return;}for(int j=i;j<(int)a.size()&&a[j]<=t;++j){if(j>i&&a[j]==a[j-1])continue;c.push_back(a[j]);go(a,j+1,t-a[j],c,r);c.pop_back();}} vector<vector<int>> combinationSum2(vector<int>a,int t){a.erase(remove_if(a.begin(),a.end(),[](int x){return x<=0;}),a.end());sort(a.begin(),a.end());vector<vector<int>>r;vector<int>c;go(a,0,t,c,r);return r;}
int main(){cout<<combinationSum2({10,1,2,7,6,1,5},8).size()<<'\n';return 0;}
