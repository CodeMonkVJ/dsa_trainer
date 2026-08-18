#include <bits/stdc++.h>
using namespace std;
int countDistinctSubstrings(const string& s){unordered_set<string>seen;for(size_t i=0;i<s.size();++i)for(size_t j=i+1;j<=s.size();++j)seen.insert(s.substr(i,j-i));return seen.size()+1;}
int main(){return 0;}

