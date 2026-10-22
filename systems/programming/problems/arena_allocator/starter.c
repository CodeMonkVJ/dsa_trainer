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

bool arena_init(Arena *arena, void *storage, size_t capacity) {
  (void)arena;
  (void)storage;
  (void)capacity; /* TODO */
  return false;
}
void *arena_alloc(Arena *arena, size_t bytes, size_t alignment) {
  (void)arena;
  (void)bytes;
  (void)alignment; /* TODO */
  return NULL;
}
ArenaMark arena_mark(const Arena *arena) {
  (void)arena; /* TODO */
  return (ArenaMark){0};
}
bool arena_rewind(Arena *arena, ArenaMark mark) {
  (void)arena;
  (void)mark; /* TODO */
  return false;
}
bool arena_reset(Arena *arena) {
  (void)arena; /* TODO */
  return false;
}
