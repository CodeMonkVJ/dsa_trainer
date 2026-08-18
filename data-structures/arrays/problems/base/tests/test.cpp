#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(const char *operation, bool ok) {
  ++total;
  cout << "DSA_CASE {\"input\":{\"operation\":\"" << operation
       << "\"},\"expected\":true,\"actual\":" << (ok ? "true" : "false")
       << ",\"passed\":" << (ok ? "true" : "false") << "}\n";
  if (ok)
    ++passed;
  cout << (ok ? "PASS " : "FAIL ") << operation << '\n';
}
int main() {
  DynamicArray arr;
  daInit(&arr);
  check("initializes empty storage",
        arr.size == 0 && arr.capacity >= 4 && arr.data != nullptr);

  for (int i = 0; i < 32; ++i)
    daPushBack(&arr, i * 2);
  check("grows without losing capacity invariant",
        arr.size == 32 && arr.capacity >= arr.size);
  check("indexed access handles boundaries", daAt(&arr, 0) == 0 &&
                                                 daAt(&arr, 31) == 62 &&
                                                 daAt(&arr, 32) == -111111);

  int value = 0;
  check("pop returns the last value",
        daPopBack(&arr, &value) && value == 62 && arr.size == 31);
  check("pop supports a null output pointer",
        daPopBack(&arr, nullptr) && arr.size == 30);

  daClear(&arr);
  check("clear makes the array empty",
        arr.size == 0 && !daPopBack(&arr, &value));
  daPushBack(&arr, 42);
  check("array remains reusable after clear",
        arr.size == 1 && daAt(&arr, 0) == 42);

  daFree(&arr);
  check("free resets the array",
        arr.data == nullptr && arr.size == 0 && arr.capacity == 0);
  cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
       << "}\n";
  return passed == total ? 0 : 1;
}
