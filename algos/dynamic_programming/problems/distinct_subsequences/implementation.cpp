#include <bits/stdc++.h>
using namespace std;
long long distinctSubsequences(const string& s,const string& t){vector<long long>d(t.size()+1);d[0]=1;for(char c:s)for(int j=static_cast<int>(t.size());j>=1;--j)if(c==t[j-1])d[j]+=d[j-1];return d.back();}
int main(){return 0;}

