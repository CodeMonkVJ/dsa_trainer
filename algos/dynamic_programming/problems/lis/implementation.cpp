#include <bits/stdc++.h>
using namespace std;
int longestIncreasingSubsequence(const vector<int>& a){vector<int> d;for(int x:a){auto it=lower_bound(d.begin(),d.end(),x);if(it==d.end())d.push_back(x);else *it=x;}return d.size();}
int main(){return 0;}

