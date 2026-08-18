#include <bits/stdc++.h>
using namespace std;
vector<vector<long long>> floydWarshall(vector<vector<long long>> d) { int n=d.size();for(int k=0;k<n;++k)for(int i=0;i<n;++i)for(int j=0;j<n;++j)if(d[i][k]<LLONG_MAX/8&&d[k][j]<LLONG_MAX/8)d[i][j]=min(d[i][j],d[i][k]+d[k][j]);return d; }

