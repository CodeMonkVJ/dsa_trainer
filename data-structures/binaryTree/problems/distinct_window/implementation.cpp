#include <bits/stdc++.h>
using namespace std;
vector<int> distinctInWindows(const vector<int>& values, int width) { if (width<=0 || width>static_cast<int>(values.size())) throw invalid_argument("invalid window"); unordered_map<int,int> counts; vector<int> result; for (int i=0;i<static_cast<int>(values.size());++i) { ++counts[values[i]]; if (i>=width && --counts[values[i-width]]==0) counts.erase(values[i-width]); if (i>=width-1) result.push_back(static_cast<int>(counts.size())); } return result; }
