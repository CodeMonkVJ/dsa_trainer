#include <bits/stdc++.h>
using namespace std;
int maxProfit(const vector<int>& prices){int low=INT_MAX,ans=0;for(int x:prices)low=min(low,x),ans=max(ans,x-low);return ans;}
int main(){return 0;}

