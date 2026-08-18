#include <bits/stdc++.h>
using namespace std;
vector<int> dfsTraversal(const vector<vector<int>>& graph, int start) { if(start<0||start>=static_cast<int>(graph.size())) throw out_of_range("vertex"); vector<int> result; vector<bool> seen(graph.size()); function<void(int)> visit=[&](int v){seen[v]=true;result.push_back(v);for(int n:graph[v]){if(n<0||n>=static_cast<int>(graph.size()))throw out_of_range("vertex");if(!seen[n])visit(n);}};visit(start);return result; }

