#include <bits/stdc++.h>
using namespace std;
int findContentChildren(vector<int> g,vector<int> s){sort(g.begin(),g.end());sort(s.begin(),s.end());size_t i=0,j=0;while(i<g.size()&&j<s.size()){if(s[j]>=g[i])++i;++j;}return int(i);}
int main(){cout<<findContentChildren({1,2,3},{1,1})<<'\n';return 0;}
