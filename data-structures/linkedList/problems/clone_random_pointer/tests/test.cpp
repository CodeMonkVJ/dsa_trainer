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
int main() {
  check(copyRandomList(nullptr) == nullptr, "empty");
  vector<Node *> o;
  for (int v : {7, 13, 11, 10, 1})
    o.push_back(new Node{v, nullptr, nullptr});
  for (int i = 0; i + 1 < (int)o.size(); ++i)
    o[i]->next = o[i + 1];
  o[0]->random = nullptr;
  o[1]->random = o[0];
  o[2]->random = o[4];
  o[3]->random = o[2];
  o[4]->random = o[0];
  Node *c = copyRandomList(o[0]);
  vector<Node *> cl;
  for (Node *p = c; p; p = p->next)
    cl.push_back(p);
  bool good = cl.size() == o.size();
  for (int i = 0; i < (int)o.size(); ++i) {
    good = good && cl[i] != o[i] && cl[i]->value == o[i]->value;
    good = good &&
           (!o[i]->random ? cl[i]->random == nullptr
                          : cl[i]->random ==
                                cl[distance(o.begin(), find(o.begin(), o.end(),
                                                            o[i]->random))]);
  }
  check(good, "copies values and random relationships");
  bool separate = true;
  for (Node *p = o[0]; p; p = p->next)
    for (Node *q = c; q; q = q->next)
      separate = separate && p != q;
  check(separate, "shares no nodes");
  for (Node *p = o[0]; p;) {
    Node *n = p->next;
    delete p;
    p = n;
  }
  for (Node *p = c; p;) {
    Node *n = p->next;
    delete p;
    p = n;
  }
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
