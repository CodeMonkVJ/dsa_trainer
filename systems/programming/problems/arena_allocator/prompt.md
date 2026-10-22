# Arena Allocator

Allocate aligned regions from caller-owned storage with bounded capacity and epoch-checked checkpoints.

## Contract

Arena uses caller-owned storage whose start is aligned to _Alignof(max_align_t). arena_init rejects null arguments or a misaligned storage pointer and otherwise initializes capacity, used=0, epoch=1. A zero capacity is valid; no allocation can succeed. The caller guarantees the supplied storage object actually contains capacity bytes and that the Arena object does not overlap it.

arena_alloc rejects zero bytes, non-power-of-two alignment, alignment above _Alignof(max_align_t), exhaustion and arithmetic overflow. Return NULL without changing used or backing storage on failure. On success reserve an aligned range, advance used, and return its start; do not clear or allocate backing memory.

arena_mark returns {owner,offset,epoch}; a null arena returns an invalid zero mark. arena_rewind accepts only a mark from that exact arena and current epoch with offset <= used. Success rewinds used and increments epoch, invalidating ALL existing marks. arena_reset sets used=0 and also increments epoch. Reject either operation if epoch would wrap; leave state unchanged. Checkpoint validation catches cross-arena and pre-reset/pre-rewind marks; reinitialization ends the arena's lifetime, so old marks must never be reused afterward.

All pointers into reclaimed space become invalid to use after reset/rewind, even if the same address is allocated again. The caller owns backing storage and frees it only after all allocations are retired. No individual free, implicit zeroing, or thread safety is promised.

## API

```c
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef struct { unsigned char *data; size_t capacity, used; uint64_t epoch; } Arena;
typedef struct { const Arena *owner; size_t offset; uint64_t epoch; } ArenaMark;
bool arena_init(Arena *arena, void *storage, size_t capacity);
void *arena_alloc(Arena *arena, size_t bytes, size_t alignment);
ArenaMark arena_mark(const Arena *arena);
bool arena_rewind(Arena *arena, ArenaMark mark);
bool arena_reset(Arena *arena);
```

Save your implementation in the editor and use **Run tests**. All tests run on the Linux x86 host. No hardware is required.
