#include <bits/stdc++.h>
using namespace std;
class DisjointSetUnion {
public:
  explicit DisjointSetUnion(int) {}
  int find(int value) { return value; }
  bool unite(int, int) { return false; }
  bool connected(int, int) { return false; }
};
