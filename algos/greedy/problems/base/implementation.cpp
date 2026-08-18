#include <bits/stdc++.h>
using namespace std;
int maxMeetings(const vector<int>& start, const vector<int>& finish) { vector<pair<int,int>> a; for(size_t i=0;i<start.size()&&i<finish.size();++i)a.push_back({finish[i],start[i]}); sort(a.begin(),a.end()); int count=0,last=numeric_limits<int>::min(); for(auto [end,beg]:a) if(beg>=last){++count;last=end;} return count; }
int main(){ cout << maxMeetings({1,3,0,5,8,5},{2,4,5,7,9,9}) << '\n'; return 0; }
