# LFU Cache

Implement an LFU cache with a positive capacity. `get(key)` returns the value for a key and increases its frequency, or returns `-1` when absent. `put(key, value)` inserts or updates a key and increases its frequency when updating. When full, evict the least frequently used key; if several keys have the same minimum frequency, evict the least recently used among them.

Both operations must run in average **O(1)** time. The cache starts empty, and updating an existing key must not increase its size.
