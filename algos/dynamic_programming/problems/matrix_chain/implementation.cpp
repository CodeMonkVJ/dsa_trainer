#include <bits/stdc++.h>
using namespace std;
long long matrixChain(const vector<int>& p){if(p.size()<2)return 0;int n=p.size()-1;vector<vector<long long>>d(n,vector<long long>(n));for(int len=2;len<=n;++len)for(int i=0;i+len<=n;++i){int j=i+len-1;d[i][j]=LLONG_MAX;for(int k=i;k<j;++k)d[i][j]=min(d[i][j],d[i][k]+d[k+1][j]+1LL*p[i]*p[k+1]*p[j]);}return d[0][n-1];}
int main(){return 0;}

