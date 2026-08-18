# LRU Cache

Implement an LRU cache with a positive capacity. `get(key)` returns the value for a key and marks it as recently used, or returns `-1` when the key is absent. `put(key, value)` inserts or updates a key and marks it as recently used. When inserting into a full cache, evict the least recently used key.

Both operations must run in average **O(1)** time. Use a hash map and a doubly linked list (or an equivalent constant-time design).

The cache starts empty. Updating an existing key must not increase its size.
