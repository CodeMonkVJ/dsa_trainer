#include <bits/stdc++.h>
using namespace std; bool pal(const string&s,int l,int r){while(l<r)if(s[l++]!=s[r--])return false;return true;} void go(const string&s,int i,vector<string>&c,vector<vector<string>>&r){if(i==(int)s.size()){r.push_back(c);return;}for(int j=i;j<(int)s.size();++j)if(pal(s,i,j)){c.push_back(s.substr(i,j-i+1));go(s,j+1,c,r);c.pop_back();}} vector<vector<string>> partition(const string&s){vector<vector<string>>r;vector<string>c;go(s,0,c,r);return r;}
int main(){cout<<partition("aab").size()<<'\n';return 0;}
