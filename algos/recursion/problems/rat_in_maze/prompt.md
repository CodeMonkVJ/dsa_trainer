# Rat in a Maze

Given a binary matrix, find all paths from the top-left cell to the bottom-right cell. A `1` is an open cell and a `0` is blocked. The rat may move one cell at a time in the four cardinal directions and may not visit a cell more than once in a path.

Implement:

```cpp
std::vector<std::string> ratInMaze(std::vector<std::vector<int>> maze);
```

Use `D`, `L`, `R`, and `U` to represent down, left, right, and up moves. Return paths in lexicographic order. Return an empty vector when the maze is empty, malformed, blocked at either endpoint, or has no route.
