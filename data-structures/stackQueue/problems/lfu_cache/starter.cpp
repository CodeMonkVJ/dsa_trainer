#include <bits/stdc++.h>
using namespace std;

class LFUCache {
public:
  explicit LFUCache(int capacity);
  int get(int key);
  void put(int key, int value);
};
