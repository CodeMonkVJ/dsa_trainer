#include <bits/stdc++.h>
using namespace std;
bool subsetSum(const vector<int>& a,int target){vector<bool>d(target+1);d[0]=true;for(int x:a)for(int s=target;s>=x;--s)d[s]=d[s]||d[s-x];return target>=0&&d[target];}
int main(){return 0;}

