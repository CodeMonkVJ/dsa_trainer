# N Meetings in One Room

Implement `int maxMeetings(const std::vector<int>& start, const std::vector<int>& finish)`.

Return the maximum number of meetings that can use one room when a meeting may start at the exact time the previous one finishes. Input arrays have matching lengths. Return zero for empty input. Aim for `O(n log n)` time by selecting meetings in increasing finish-time order.
