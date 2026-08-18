#include <bits/stdc++.h>
using namespace std;
bool wordBreak(const string& s,const vector<string>& dictionary){unordered_set<string>words(dictionary.begin(),dictionary.end());vector<bool>d(s.size()+1);d[0]=true;for(size_t i=1;i<=s.size();++i)for(size_t j=0;j<i;++j)if(d[j]&&words.count(s.substr(j,i-j))){d[i]=true;break;}return d[s.size()];}
int main(){return 0;}

