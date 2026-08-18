#include <bits/stdc++.h>
using namespace std;
string longestWord(vector<string> words){unordered_set<string>s(words.begin(),words.end());string ans;for(const string&w:words){bool good=true;for(size_t i=1;i<=w.size();++i)if(!s.count(w.substr(0,i)))good=false;if(good&&(w.size()>ans.size()||(w.size()==ans.size()&&w<ans)))ans=w;}return ans;}
int main(){return 0;}

