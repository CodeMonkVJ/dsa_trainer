#include <bits/stdc++.h>
using namespace std;
int minCoins(int amount,vector<int> coins){if(amount<0)return -1;sort(coins.rbegin(),coins.rend());int count=0;for(int coin:coins)if(coin>0){count+=amount/coin;amount%=coin;}return amount==0?count:-1;}
int main(){cout<<minCoins(70,{1,2,5,10,20,50})<<'\n';return 0;}
