#include <bits/stdc++.h>
using namespace std;
struct Node {
  int val;
  vector<Node *> neighbors;
  Node(int v) : val(v) {}
};
Node *cloneGraph(Node *) { return nullptr; }
