#include <bits/stdc++.h>
using namespace std; void go(vector<int>&a,int i,vector<int>&cur,vector<vector<int>>&r){r.push_back(cur);for(int j=i;j<(int)a.size();++j){if(j>i&&a[j]==a[j-1])continue;cur.push_back(a[j]);go(a,j+1,cur,r);cur.pop_back();}} vector<vector<int>> subsetsWithDup(vector<int>a){sort(a.begin(),a.end());vector<vector<int>>r;vector<int>c;go(a,0,c,r);return r;}
int main(){cout<<subsetsWithDup({1,2,2}).size()<<'\n';return 0;}
