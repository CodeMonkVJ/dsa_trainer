#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  DisjointSetUnion dsu(5);
  check(dsu.unite(0, 1) && dsu.unite(1, 2), "union components");
  check(dsu.connected(0, 2) && !dsu.connected(0, 3), "connectivity");
  check(!dsu.unite(0, 2), "duplicate union");
  bool rejected = false; try { (void)dsu.find(5); } catch (const out_of_range&) { rejected = true; }
  check(rejected, "invalid index");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
