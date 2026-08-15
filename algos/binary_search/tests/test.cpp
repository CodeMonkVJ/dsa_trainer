#include <iostream>
#include <string>
#include <vector>

#ifndef DSA_IMPLEMENTATION
#define DSA_IMPLEMENTATION "../implementation.cpp"
#endif

#include DSA_IMPLEMENTATION

namespace {

int passed = 0;
int total = 0;

void check(const std::string& name, const std::vector<int>& values, int target,
           int expected) {
    ++total;
    const int actual = binarySearch(values, target);
    if (actual == expected) {
        ++passed;
        std::cout << "PASS " << name << '\n';
        return;
    }
    std::cout << "FAIL " << name << ": expected " << expected << ", got "
              << actual << '\n';
}

}  // namespace

int main() {
    check("empty", {}, 4, -1);
    check("singleton present", {4}, 4, 0);
    check("singleton absent", {4}, 3, -1);
    check("first element", {1, 3, 5, 7}, 1, 0);
    check("middle element", {1, 3, 5, 7}, 5, 2);
    check("last element", {1, 3, 5, 7}, 7, 3);
    check("below range", {1, 3, 5, 7}, -5, -1);
    check("above range", {1, 3, 5, 7}, 10, -1);
    check("between elements", {1, 3, 5, 7}, 4, -1);
    check("first duplicate", {1, 2, 2, 2, 4}, 2, 1);
    check("all duplicates", {8, 8, 8, 8}, 8, 0);
    check("negative values", {-10, -4, -4, 0, 6}, -4, 1);

    std::cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
              << "}\n";
    return passed == total ? 0 : 1;
}
