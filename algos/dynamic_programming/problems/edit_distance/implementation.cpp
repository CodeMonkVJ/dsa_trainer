#include <bits/stdc++.h>
using namespace std;
int editDistance(const string& a,const string& b){vector<int>d(b.size()+1);iota(d.begin(),d.end(),0);for(size_t i=1;i<=a.size();++i){int diag=d[0];d[0]=i;for(size_t j=1;j<=b.size();++j){int old=d[j];d[j]=a[i-1]==b[j-1]?diag+0:1+min({diag,d[j],d[j-1]});diag=old;}}return d.back();}
int main(){return 0;}

