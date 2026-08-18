#include <bits/stdc++.h>
using namespace std;
class TrieII{unordered_map<string,int> words,prefixes;public:void insert(const string& w){++words[w];for(size_t i=1;i<=w.size();++i)++prefixes[w.substr(0,i)];}int countWordsEqualTo(const string& w)const{auto it=words.find(w);return it==words.end()?0:it->second;}int countWordsStartingWith(const string& p)const{auto it=prefixes.find(p);return it==prefixes.end()?0:it->second;}void erase(const string& w){auto it=words.find(w);if(it==words.end()||it->second==0)return;if(--it->second==0)words.erase(it);for(size_t i=1;i<=w.size();++i)if(--prefixes[w.substr(0,i)]==0)prefixes.erase(w.substr(0,i));}};
int main(){return 0;}

