/**
 * Convert the leading integer in a string to a signed 32-bit value.
 *
 * Time: O(n) in the number of inspected characters
 * Extra space: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

static int parseAtoi(const string& value) {
    size_t index = 0;
    while (index < value.size() && value[index] == ' ') ++index;

    int sign = 1;
    if (index < value.size() && (value[index] == '+' || value[index] == '-')) {
        if (value[index] == '-') sign = -1;
        ++index;
    }

    long long number = 0;
    while (index < value.size() && value[index] >= '0' && value[index] <= '9') {
        number = number * 10 + (value[index] - '0');
        long long signedValue = sign * number;
        if (signedValue > INT_MAX) return INT_MAX;
        if (signedValue < INT_MIN) return INT_MIN;
        ++index;
    }
    return static_cast<int>(sign * number);
}

int main() {
    cout << parseAtoi("  -42") << '\n';
    return 0;
}
