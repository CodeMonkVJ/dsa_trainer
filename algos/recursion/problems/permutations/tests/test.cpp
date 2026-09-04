#include <bits/stdc++.h>
using namespace std;
#include "../../../../../test_protocol.hpp"

#define main dsa_reference_main
#include DSA_IMPLEMENTATION
#undef main

int passed = 0;
int total = 0;

void check(bool condition, const char *input, bool expected) {
  ++total;
  if (condition)
    ++passed;
  dsa_test::emit_case(input, expected ? "true" : "false",
                      condition ? "true" : "false", condition == expected);
}

set<vector<int>> asSet(vector<vector<int>> values) {
  return {values.begin(), values.end()};
}

// int main() {
  // check(asSet(permutations({1, 2, 3})) == asSet({{1, 2, 3},
  //                                                {1, 3, 2},
  //                                                {2, 1, 3},
  //                                                {2, 3, 1},
  //                                                {3, 1, 2},
  //                                                {3, 2, 1}}),
  //       R"({"values":[1,2,3]})", true);
  // check(asSet(permutations({1, 1, 2})) ==
  //           asSet({{1, 1, 2}, {1, 2, 1}, {2, 1, 1}}),
  //       R"({"values":[1,1,2]})", true);
  // check(permutations({}).size() == 1 && permutations({})[0].empty(),
  //       R"({"values":[]})", true);
  // check(asSet(permutations({-1, 0, -1})) ==
  //           asSet({{-1, -1, 0}, {-1, 0, -1}, {0, -1, -1}}),
  //       R"({"values":[-1,0,-1]})", true);
  // check(permutations({7}).size() == 1 && permutations({7})[0] == vector<int>{7},
  //       R"({"values":[7]})", true);



//   cout << "DSA_RESULT {\"passed\":" << passed << ",\"total\":" << total
//        << "}\n";
//   return passed == total ? 0 : 1;
// }


int main() {
  check(asSet(permutations({1, 2, 3})) ==
            asSet({{1, 2, 3},
                   {1, 3, 2},
                   {2, 1, 3},
                   {2, 3, 1},
                   {3, 1, 2},
                   {3, 2, 1}}),
        R"({"values":[1,2,3]})", true);

  check(asSet(permutations({1, 1, 2})) ==
            asSet({{1, 1, 2},
                   {1, 2, 1},
                   {2, 1, 1}}),
        R"({"values":[1,1,2]})", true);

  {
    auto result = permutations({1, 1, 2});
    check(result.size() == 3 &&
              asSet(result).size() == 3,
          R"({"values":[1,1,2],"check":"no-duplicates"})", true);
  }

  {
    auto result = permutations({1, 1, 1});
    check(result.size() == 1 &&
              result[0] == vector<int>({1, 1, 1}),
          R"({"values":[1,1,1]})", true);
  }

  {
    auto result = permutations({1, 1, 2, 2});
    check(result.size() == 6 &&
              asSet(result).size() == 6,
          R"({"values":[1,1,2,2]})", true);
  }

  check(permutations({}).size() == 1 &&
            permutations({})[0].empty(),
        R"({"values":[]})", true);

  check(asSet(permutations({-1, 0, -1})) ==
            asSet({{-1, -1, 0},
                   {-1, 0, -1},
                   {0, -1, -1}}),
        R"({"values":[-1,0,-1]})", true);

  check(permutations({7}).size() == 1 &&
            permutations({7})[0] == vector<int>{7},
        R"({"values":[7]})", true);

  {
    auto result = permutations({0, 0});
    check(result.size() == 1 &&
              result[0] == vector<int>({0, 0}),
          R"({"values":[0,0]})", true);
  }

  {
    auto result = permutations({2, 1, 1});
    check(result.size() == 3 &&
              asSet(result) ==
                  asSet({{1, 1, 2},
                         {1, 2, 1},
                         {2, 1, 1}}),
          R"({"values":[2,1,1]})", true);
  }

  {
    auto result = permutations({1, 1, 2, 3});

    check(result.size() == 12 &&
              asSet(result).size() == 12,
          R"({"values":[1,1,2,3]})", true);
  }

  {
    auto result = permutations({2, 2, 2, 3, 3});

    check(result.size() == 10 &&
              asSet(result).size() == 10,
          R"({"values":[2,2,2,3,3]})", true);
  }

  cout << "DSA_RESULT {\"passed\":" << passed
       << ",\"total\":" << total << "}\n";

  return passed == total ? 0 : 1;
}