#include <bits/stdc++.h>
using namespace std;
bool canPartition(const vector<int>& a){int sum=accumulate(a.begin(),a.end(),0);if(sum%2)return false;int target=sum/2;vector<bool>d(target+1);d[0]=true;for(int x:a)for(int s=target;s>=x;--s)d[s]=d[s]||d[s-x];return d[target];}
int main(){return 0;}
