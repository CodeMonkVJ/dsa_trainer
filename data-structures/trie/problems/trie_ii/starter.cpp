#include <bits/stdc++.h>
using namespace std;
class TrieII {
public:
  void insert(const string &);
  int countWordsEqualTo(const string &) const;
  int countWordsStartingWith(const string &) const;
  void erase(const string &);
};
