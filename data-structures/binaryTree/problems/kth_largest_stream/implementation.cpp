#include <bits/stdc++.h>
using namespace std;
class KthLargest { int k; priority_queue<int,vector<int>,greater<int>> heap; public: KthLargest(int rank, const vector<int>& values): k(rank) { if (k<=0) throw invalid_argument("k must be positive"); for (int value: values) { heap.push(value); if (static_cast<int>(heap.size())>k) heap.pop(); } } int add(int value) { heap.push(value); if (static_cast<int>(heap.size())>k) heap.pop(); if (static_cast<int>(heap.size())<k) throw invalid_argument("not enough values"); return heap.top(); } };
