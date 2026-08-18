#include <bits/stdc++.h>

using namespace std;

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(const char *name, const string &input, const string &expected,
           const string &actual, bool ok) {
  ++total;
  if (ok)
    ++passed;
  cout << "DSA_CASE {\"input\":" << input << ",\"expected\":" << expected
       << ",\"actual\":" << actual << ",\"passed\":" << (ok ? "true" : "false")
       << "}\n";
  cout << (ok ? "PASS " : "FAIL ") << name << '\n';
}

int main() {
  DisjointSetUnion dsu(5);

  const bool firstUnion = dsu.unite(0, 1);
  const bool secondUnion = dsu.unite(1, 2);
  check("union components",
        "{\"count\":5,\"operations\":[[\"unite\",0,1],[\"unite\",1,2]]}",
        "{\"united\":[true,true]}",
        string("{\"united\":[") + (firstUnion ? "true" : "false") + "," +
            (secondUnion ? "true" : "false") + "]}",
        firstUnion && secondUnion);

  const bool connected = dsu.connected(0, 2);
  const bool separated = !dsu.connected(0, 3);
  check(
      "connectivity",
      "{\"count\":5,\"operations\":[[\"connected\",0,2],[\"connected\",0,3]]}",
      "{\"connected\":[true,false]}",
      string("{\"connected\":[") + (connected ? "true" : "false") + "," +
          (separated ? "false" : "true") + "]}",
      connected && separated);

  const bool duplicateUnion = dsu.unite(0, 2);
  check("duplicate union", "{\"count\":5,\"operation\":[\"unite\",0,2]}",
        "{\"united\":false}",
        string("{\"united\":") + (duplicateUnion ? "true}" : "false}"),
        !duplicateUnion);

  bool rejected = false;
  try {
    (void)dsu.find(5);
  } catch (const out_of_range &) {
    rejected = true;
  }
  check("invalid index", "{\"count\":5,\"operation\":[\"find\",5]}",
        "{\"throws\":\"out_of_range\"}",
        rejected ? "{\"throws\":\"out_of_range\"}" : "{\"throws\":null}",
        rejected);

  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
