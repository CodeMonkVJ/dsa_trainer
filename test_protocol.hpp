#pragma once

#include <iostream>
#include <string_view>

namespace dsa_test {

inline void emit_case(std::string_view input, std::string_view expected,
                      std::string_view actual, bool passed) {
    std::cout << "DSA_CASE {\"input\":" << input << ",\"expected\":"
              << expected << ",\"actual\":" << actual
              << ",\"passed\":" << (passed ? "true" : "false")
              << "}\n";
}

}  // namespace dsa_test
