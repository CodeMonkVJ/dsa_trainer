#include <bits/stdc++.h>
using namespace std; void go(const vector<int>&a,int i,int sum,vector<int>&r){if(i==(int)a.size()){r.push_back(sum);return;}go(a,i+1,sum,r);go(a,i+1,sum+a[i],r);} vector<int> subsetSums(const vector<int>&a){vector<int>r;go(a,0,0,r);return r;}
int main(){for(int x:subsetSums({1,2,3}))cout<<x<<' ';return 0;}
