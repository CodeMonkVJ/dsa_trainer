#include <bits/stdc++.h>
using namespace std;
int kthLargest(const vector<int>& values, int k) { if (k<=0 || k>static_cast<int>(values.size())) throw invalid_argument("invalid k"); priority_queue<int,vector<int>,greater<int>> heap; for (int value: values) { heap.push(value); if (static_cast<int>(heap.size())>k) heap.pop(); } return heap.top(); }
