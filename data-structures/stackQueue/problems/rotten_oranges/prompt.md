# Rotten Oranges

You are given a grid where `0` is an empty cell, `1` is a fresh orange, and `2` is a rotten orange. Every minute, a rotten orange makes each directly adjacent fresh orange rotten. Return the minimum number of minutes required until no fresh orange remains. Return `-1` if some fresh orange can never rot.

Return `0` when there are no fresh oranges. Use a multi-source breadth-first search starting from all rotten oranges.
