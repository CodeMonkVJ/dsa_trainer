#include <bits/stdc++.h>
using namespace std;

class LRUCache {
public:
  explicit LRUCache(int capacity);
  int get(int key);
  void put(int key, int value);
};
