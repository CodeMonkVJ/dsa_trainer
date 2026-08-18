#include <bits/stdc++.h>
using namespace std;
bool wildcardMatch(const string& s,const string& p){vector<bool>d(p.size()+1);d[0]=true;for(size_t j=1;j<=p.size();++j)d[j]=d[j-1]&&p[j-1]=='*';for(char c:s){vector<bool>n(p.size()+1);for(size_t j=1;j<=p.size();++j)n[j]=p[j-1]=='*'?(n[j-1]||d[j]):((p[j-1]=='?'||p[j-1]==c)&&d[j-1]);d.swap(n);}return d.back();}
int main(){return 0;}

