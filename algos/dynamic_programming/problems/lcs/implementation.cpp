#include <bits/stdc++.h>
using namespace std;
int longestCommonSubsequence(const string& a,const string& b){vector<int>d(b.size()+1);for(char x:a){int diag=0;for(size_t j=1;j<=b.size();++j){int old=d[j];d[j]=x==b[j-1]?diag+1:max(d[j],d[j-1]);diag=old;}}return d.back();}
int main(){return 0;}

