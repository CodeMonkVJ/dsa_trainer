#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef struct {
  unsigned char *data;
  size_t capacity, used;
  uint64_t epoch;
} Arena;
typedef struct {
  const Arena *owner;
  size_t offset;
  uint64_t epoch;
} ArenaMark;
bool arena_init(Arena *arena, void *storage, size_t capacity);
void *arena_alloc(Arena *arena, size_t bytes, size_t alignment);
ArenaMark arena_mark(const Arena *arena);
bool arena_rewind(Arena *arena, ArenaMark mark);
bool arena_reset(Arena *arena);

bool arena_init(Arena *a, void *storage, size_t cap) {
  if (!a || !storage || (uintptr_t)storage % _Alignof(max_align_t))
    return false;
  *a = (Arena){.data = storage, .capacity = cap, .epoch = 1};
  return true;
}
void *arena_alloc(Arena *a, size_t bytes, size_t align) {
  if (!a || !bytes || !align || (align & (align - 1)) ||
      align > _Alignof(max_align_t))
    return NULL;
  if (a->used > a->capacity)
    return NULL;
  size_t padding = (align - (a->used & (align - 1))) & (align - 1);
  if (padding > a->capacity - a->used ||
      bytes > a->capacity - a->used - padding)
    return NULL;
  size_t offset = a->used + padding;
  a->used = offset + bytes;
  return a->data + offset;
}
ArenaMark arena_mark(const Arena *a) {
  if (!a)
    return (ArenaMark){0};
  return (ArenaMark){a, a->used, a->epoch};
}
bool arena_rewind(Arena *a, ArenaMark mark) {
  if (!a || mark.owner != a || mark.epoch != a->epoch ||
      mark.offset > a->used || a->epoch == UINT64_MAX)
    return false;
  a->used = mark.offset;
  ++a->epoch;
  return true;
}
bool arena_reset(Arena *a) {
  if (!a || a->epoch == UINT64_MAX)
    return false;
  a->used = 0;
  ++a->epoch;
  return true;
}
