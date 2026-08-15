#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  HashTable table{}; check(htInit(&table, 2, 0.75), "initialize table");
  check(htPut(&table, "alpha", 1) && htPut(&table, "beta", 2) && htPut(&table, "gamma", 3), "insert and resize");
  int value = 0; check(htGet(&table, "beta", &value) && value == 2, "lookup value");
  check(htPut(&table, "beta", 20) && htGet(&table, "beta", &value) && value == 20, "update existing key");
  check(htContains(&table, "alpha") && !htContains(&table, "missing"), "contains");
  check(htRemove(&table, "alpha") && !htContains(&table, "alpha") && !htRemove(&table, "alpha"), "remove");
  size_t longest = 0, empty = 0; check(htBucketStats(&table, &longest, &empty) > 0 && htLoadFactor(&table) > 0, "bucket statistics");
  htClear(&table); check(table.buckets == nullptr && table.size == 0, "clear and ownership");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
