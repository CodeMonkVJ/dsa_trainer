#include <bits/stdc++.h>
using namespace std;
int rodCutting(const vector<int>& price,int length){vector<int>d(length+1);for(int n=1;n<=length;++n)for(int cut=1;cut<=n&&cut<=static_cast<int>(price.size());++cut)d[n]=max(d[n],price[cut-1]+d[n-cut]);return d[length];}
int main(){return 0;}

