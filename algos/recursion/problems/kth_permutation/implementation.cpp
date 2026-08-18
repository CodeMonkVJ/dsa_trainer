#include <bits/stdc++.h>
using namespace std; string getPermutation(int n,int k){if(n<1||n>9||k<1)return {};vector<int>a;long long fact=1;for(int i=1;i<=n;++i){a.push_back(i);fact*=i;}if(k>fact)return {};--k;string r;for(int left=n;left;--left){fact/=left;int idx=int(k/fact);k%=fact;r+=char('0'+a[idx]);a.erase(a.begin()+idx);}return r;}
int main(){cout<<getPermutation(3,4)<<'\n';return 0;}
