#include <bits/stdc++.h>
using namespace std; void go(vector<int>&a,int i,int t,vector<int>&c,vector<vector<int>>&r){if(!t){r.push_back(c);return;}for(int j=i;j<(int)a.size()&&a[j]<=t;++j){c.push_back(a[j]);go(a,j,t-a[j],c,r);c.pop_back();}} vector<vector<int>> combinationSum(vector<int>a,int t){a.erase(remove_if(a.begin(),a.end(),[](int x){return x<=0;}),a.end());sort(a.begin(),a.end());a.erase(unique(a.begin(),a.end()),a.end());vector<vector<int>>r;vector<int>c;go(a,0,t,c,r);return r;}
int main(){cout<<combinationSum({2,3,6,7},7).size()<<'\n';return 0;}
