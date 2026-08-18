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
vector<int> values(DList *list) {
  vector<int> result;
  for (size_t i = 0; i < list->size; ++i)
    result.push_back(dlAt(list, i));
  return result;
}
int main() {
  DList list;
  dlInit(&list);
  dlPushBack(&list, 10);
  dlPushBack(&list, 20);
  dlPushFront(&list, 5);
  check(values(&list) == vector<int>({5, 10, 20}) &&
            list.head->prev == nullptr && list.tail->next == nullptr,
        "end operations and links");
  check(dlInsertAt(&list, 2, 15) &&
            values(&list) == vector<int>({5, 10, 15, 20}),
        "indexed insertion");
  int out = 0;
  check(dlEraseAt(&list, 1, &out) && out == 10 &&
            values(&list) == vector<int>({5, 15, 20}),
        "indexed erase");
  check(dlFind(&list, 15) != nullptr && dlAt(&list, 99) == -123123,
        "find and invalid access");
  dlClear(&list);
  check(list.size == 0 && list.head == nullptr && list.tail == nullptr,
        "clear resets list");
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
