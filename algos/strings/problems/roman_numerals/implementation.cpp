#include <bits/stdc++.h>
using namespace std;

static int romanToInteger(const string& numeral) {
    unordered_map<char, int> value{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
                                    {'C', 100}, {'D', 500}, {'M', 1000}};
    int total = 0;
    for (size_t i = 0; i < numeral.size(); ++i) {
        int current = value[numeral[i]];
        if (i + 1 < numeral.size() && current < value[numeral[i + 1]])
            total -= current;
        else
            total += current;
    }
    return total;
}

static string integerToRoman(int value) {
    if (value < 1 || value > 3999) return {};
    const vector<pair<int, string>> symbols{{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
                                             {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
                                             {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
    string result;
    for (const auto& [number, symbol] : symbols) {
        while (value >= number) {
            result += symbol;
            value -= number;
        }
    }
    return result;
}

int main() {
    cout << romanToInteger("MCMXCIV") << '\n';
    return 0;
}
