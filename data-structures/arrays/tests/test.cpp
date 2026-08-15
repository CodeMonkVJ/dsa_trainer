#include <bits/stdc++.h>
using namespace std;
#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main
int passed = 0, total = 0;
void check(bool ok, const char* name) { ++total; if (ok) ++passed; cout << (ok ? "PASS " : "FAIL ") << name << '\n'; }
int main() {
  DynamicArray arr; daInit(&arr); for (int i = 0; i < 10; ++i) daPushBack(&arr, i * 2);
  check(arr.size == 10 && daAt(&arr, 0) == 0 && daAt(&arr, 9) == 18, "growth and indexed access");
  int value = 0; check(daPopBack(&arr, &value) && value == 18 && arr.size == 9, "pop returns last value");
  daClear(&arr); check(arr.size == 0 && !daPopBack(&arr, nullptr), "clear and empty pop");
  daFree(&arr); cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total << "}\n";
  return passed == total ? 0 : 1;
}
