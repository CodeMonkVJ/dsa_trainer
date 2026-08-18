#include <bits/stdc++.h>
using namespace std;
vector<int> bfsTraversal(const vector<vector<int>>& graph, int start) { if(start<0||start>=static_cast<int>(graph.size()))throw out_of_range("vertex"); vector<int> r;vector<bool> seen(graph.size());queue<int> q;q.push(start);seen[start]=true;while(!q.empty()){int v=q.front();q.pop();r.push_back(v);for(int n:graph[v]){if(n<0||n>=static_cast<int>(graph.size()))throw out_of_range("vertex");if(!seen[n])seen[n]=true,q.push(n);}}return r; }

