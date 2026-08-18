#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char *name) {
  ++total;
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << name << std::endl;
  std::string input = std::string("{\"test\":\"") + name + "\"}";
  dsa_test::emit_case(input, ok ? "true" : "false", ok ? "true" : "false", ok);
}
vector<int> read(Node *h, bool &ok) {
  vector<int> v;
  int guard = 0;
  for (; h && guard++ < 100; h = h->bottom) {
    v.push_back(h->value);
    ok = ok && h->next == nullptr;
  }
  ok = ok && guard < 100;
  return v;
}
int main() {
  check(flatten(nullptr) == nullptr, "empty");
  Node *a = new Node{1, nullptr, nullptr}, *b = new Node{4, nullptr, nullptr},
       *c = new Node{2, nullptr, nullptr}, *d = new Node{3, nullptr, nullptr};
  a->bottom = b;
  c->bottom = d;
  a->next = c;
  Node *out = flatten(a);
  bool ok = true;
  check(read(out, ok) == vector<int>({1, 2, 3, 4}) && ok,
        "merges sorted columns");
  set<Node *> nodes{a, b, c, d};
  for (Node *p = out; p; p = p->bottom)
    nodes.erase(p);
  check(nodes.empty(), "reuses every node");
  for (Node *p = out; p;) {
    Node *n = p->bottom;
    delete p;
    p = n;
  }
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
