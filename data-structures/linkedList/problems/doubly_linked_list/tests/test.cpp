#include "../../../../../test_protocol.hpp"
#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool ok, const char *name) {
  ++total;

  if (ok)
    ++passed;

  cout << (ok ? "PASS " : "FAIL ") << name << '\n';

  string input =
      string("{\"test\":\"") + name + "\"}";

  dsa_test::emit_case(
      input,
      "true",
      ok ? "true" : "false",
      ok);
}

vector<int> values(DList *list) {
  vector<int> result;

  for (size_t i = 0; i < list->size; ++i)
    result.push_back(dlAt(list, i));

  return result;
}

bool linksValid(DList *list) {
  if (list->size == 0)
    return list->head == nullptr && list->tail == nullptr;

  if (list->head == nullptr || list->tail == nullptr)
    return false;

  if (list->head->prev != nullptr)
    return false;

  if (list->tail->next != nullptr)
    return false;

  Node *curr = list->head;
  Node *prev = nullptr;
  size_t count = 0;

  while (curr != nullptr) {
    if (curr->prev != prev)
      return false;

    prev = curr;
    curr = curr->next;
    ++count;
  }

  return count == list->size && prev == list->tail;
}

int main() {
  // Empty list
  {
    DList list;
    dlInit(&list);

    check(list.size == 0 &&
              list.head == nullptr &&
              list.tail == nullptr &&
              dlFind(&list, 10) == nullptr &&
              dlAt(&list, 0) == -1,
          "empty list");

    dlClear(&list);
  }

  // Push front/back
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);
    dlPushFront(&list, 5);

    check(values(&list) == vector<int>({5, 10, 20}) &&
              list.size == 3 &&
              linksValid(&list),
          "push front and back");

    dlClear(&list);
  }

  // Single-element invariants
  {
    DList list;
    dlInit(&list);

    dlPushFront(&list, 42);

    check(list.size == 1 &&
              list.head == list.tail &&
              list.head->prev == nullptr &&
              list.head->next == nullptr &&
              dlAt(&list, 0) == 42 &&
              linksValid(&list),
          "single element");

    dlClear(&list);
  }

  // Indexed insertion in the middle
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);
    dlPushBack(&list, 30);

    check(dlInsertAt(&list, 1, 15) &&
              values(&list) == vector<int>({10, 15, 20, 30}) &&
              list.size == 4 &&
              linksValid(&list),
          "indexed insertion in middle");

    dlClear(&list);
  }

  // Insert at front
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 20);
    dlPushBack(&list, 30);

    check(dlInsertAt(&list, 0, 10) &&
              values(&list) == vector<int>({10, 20, 30}) &&
              list.head->value == 10 &&
              linksValid(&list),
          "indexed insertion at front");

    dlClear(&list);
  }

  // Insert at back
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);

    check(dlInsertAt(&list, 2, 30) &&
              values(&list) == vector<int>({10, 20, 30}) &&
              list.tail->value == 30 &&
              linksValid(&list),
          "indexed insertion at back");

    dlClear(&list);
  }

  // Invalid insertion
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);

    check(!dlInsertAt(&list, 99, 30) &&
              values(&list) == vector<int>({10, 20}) &&
              list.size == 2 &&
              linksValid(&list),
          "reject invalid insertion index");

    dlClear(&list);
  }

  // Erase middle
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);
    dlPushBack(&list, 30);

    int out = 0;

    check(dlEraseAt(&list, 1, &out) &&
              out == 20 &&
              values(&list) == vector<int>({10, 30}) &&
              list.size == 2 &&
              linksValid(&list),
          "erase middle");

    dlClear(&list);
  }

  // Erase front and back
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);
    dlPushBack(&list, 30);

    int out = 0;

    bool frontOk =
        dlEraseAt(&list, 0, &out) &&
        out == 10 &&
        values(&list) == vector<int>({20, 30});

    bool backOk =
        dlEraseAt(&list, 1, &out) &&
        out == 30 &&
        values(&list) == vector<int>({20});

    check(frontOk &&
              backOk &&
              list.size == 1 &&
              linksValid(&list),
          "erase front and back");

    dlClear(&list);
  }

  // Pop front/back
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);

    int out = 0;

    bool frontOk =
        dlPopFront(&list, &out) &&
        out == 10 &&
        values(&list) == vector<int>({20});

    bool backOk =
        dlPopBack(&list, &out) &&
        out == 20 &&
        list.size == 0 &&
        list.head == nullptr &&
        list.tail == nullptr;

    check(frontOk && backOk,
          "pop front and back");

    dlClear(&list);
  }

  // Pop single element
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 99);

    int out = 0;

    check(dlPopFront(&list, &out) &&
              out == 99 &&
              list.size == 0 &&
              list.head == nullptr &&
              list.tail == nullptr,
          "pop single element");

    dlClear(&list);
  }

  // Find existing and missing values
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 5);
    dlPushBack(&list, 10);
    dlPushBack(&list, 15);

    check(dlFind(&list, 10) != nullptr &&
              dlFind(&list, 10)->value == 10 &&
              dlFind(&list, 999) == nullptr,
          "find existing and missing");

    dlClear(&list);
  }

  // Invalid access
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);

    check(dlAt(&list, 0) == 10 &&
              dlAt(&list, 1) == 20 &&
              dlAt(&list, 2) == -1 &&
              dlAt(&list, 99) == -1,
          "valid and invalid access");

    dlClear(&list);
  }

  // Clear
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 10);
    dlPushBack(&list, 20);
    dlPushBack(&list, 30);

    dlClear(&list);

    check(list.size == 0 &&
              list.head == nullptr &&
              list.tail == nullptr &&
              linksValid(&list),
          "clear resets list");
  }

  // Reuse after clear
  {
    DList list;
    dlInit(&list);

    dlPushBack(&list, 1);
    dlPushBack(&list, 2);
    dlClear(&list);

    bool ok =
        dlPushFront(&list, 42) &&
        list.size == 1 &&
        list.head == list.tail &&
        dlAt(&list, 0) == 42 &&
        linksValid(&list);

    check(ok, "reuse after clear");

    dlClear(&list);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}