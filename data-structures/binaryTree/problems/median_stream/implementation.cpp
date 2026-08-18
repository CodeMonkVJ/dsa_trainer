#include <bits/stdc++.h>
using namespace std;
class MedianStream { priority_queue<int> lower; priority_queue<int,vector<int>,greater<int>> upper; public: void add(int value) { lower.push(value); upper.push(lower.top()); lower.pop(); if (upper.size()>lower.size()) { lower.push(upper.top()); upper.pop(); } } double median() const { if (lower.empty()) throw invalid_argument("empty stream"); if (lower.size()==upper.size()) return (static_cast<double>(lower.top())+upper.top())/2.0; return lower.top(); } };
