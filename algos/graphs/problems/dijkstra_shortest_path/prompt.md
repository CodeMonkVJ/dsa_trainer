# Dijkstra's Shortest Path

Implement Dijkstra's algorithm for a directed graph with non-negative edge weights.

Use the existing `WeightedEdge` representation and return the shortest distance from `source` to every vertex. Keep unreachable vertices at `INF`.

Requirements:

- Use a priority queue and stale-entry skipping.
- Reject the assumption that negative edges are valid input.
- Target complexity: `O((V + E) log V)` time.
