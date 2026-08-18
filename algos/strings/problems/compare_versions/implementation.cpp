/**
 * Compare Version Numbers
 *
 * Compares normalized components directly as strings, so arbitrarily long
 * numeric components are supported without integer overflow.
 *
 * Time: O(version1 length + version2 length)
 * Extra space: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

static pair<size_t, size_t> normalizedComponent(const string& version, size_t start) {
    size_t end = version.find('.', start);
    if (end == string::npos) end = version.size();
    while (start < end && version[start] == '0') ++start;
    return {start, end};
}

static int compareVersion(const string& version1, const string& version2) {
    size_t i = 0, j = 0;
    while (i < version1.size() || j < version2.size()) {
        auto first = normalizedComponent(version1, i);
        auto second = normalizedComponent(version2, j);
        size_t firstLength = first.second - first.first;
        size_t secondLength = second.second - second.first;

        if (firstLength != secondLength)
            return firstLength < secondLength ? -1 : 1;
        if (version1.compare(first.first, firstLength, version2, second.first, secondLength) != 0)
            return version1.compare(first.first, firstLength, version2, second.first, secondLength) < 0 ? -1 : 1;

        i = first.second == version1.size() ? version1.size() : first.second + 1;
        j = second.second == version2.size() ? version2.size() : second.second + 1;
    }
    return 0;
}

int main() {
    cout << compareVersion("1.01", "1.001") << '\n';
    return 0;
}
