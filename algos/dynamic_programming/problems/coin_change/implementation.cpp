#include <bits/stdc++.h>
using namespace std;
int coinChange(const vector<int>& coins,int amount){const int inf=1e9;vector<int>d(amount+1,inf);d[0]=0;for(int x=1;x<=amount;++x)for(int c:coins)if(c>0&&c<=x)d[x]=min(d[x],d[x-c]+1);return d[amount]==inf?-1:d[amount];}
int main(){return 0;}

