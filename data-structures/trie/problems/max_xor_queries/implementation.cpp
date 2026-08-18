#include <bits/stdc++.h>
using namespace std;
vector<int> maxXorQueries(const vector<int>& nums,const vector<pair<int,int>>& queries){vector<int>r;for(auto [x,m]:queries){int best=-1;for(int n:nums)if(n<=m)best=max(best,x^n);r.push_back(best);}return r;}
int main(){return 0;}

