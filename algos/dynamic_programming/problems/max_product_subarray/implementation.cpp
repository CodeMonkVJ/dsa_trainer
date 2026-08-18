#include <bits/stdc++.h>
using namespace std;
long long maxProductSubarray(const vector<int>& a){long long hi=a[0],lo=a[0],ans=a[0];for(size_t i=1;i<a.size();++i){long long x=a[i];if(x<0)swap(hi,lo);hi=max(x,hi*x);lo=min(x,lo);ans=max(ans,hi);}return ans;}
int main(){return 0;}

