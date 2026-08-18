#include <bits/stdc++.h>
using namespace std;
int minPalindromeCuts(const string& s){int n=s.size();vector<int>d(n+1);iota(d.begin(),d.end(),-1);for(int i=0;i<n;++i)for(int j=i;j<n;++j){bool pal=true;for(int l=i,r=j;l<r;++l,--r)if(s[l]!=s[r])pal=false;if(pal)d[j+1]=min(d[j+1],d[i]+1);}return d[n];}
int main(){return 0;}

