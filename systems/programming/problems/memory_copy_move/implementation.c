#include <stdbool.h>
#include <stddef.h>
bool byte_copy(void *dst, size_t capacity, const void *src, size_t n);
bool byte_move(void *dst, size_t capacity, const void *src, size_t n);

#include <stdlib.h>
bool byte_copy(void *dst, size_t cap, const void *src, size_t n) {
  if (n > cap || (n && (!dst || !src)))
    return false;
  unsigned char *d = dst;
  const unsigned char *s = src;
  for (size_t i = 0; i < n; ++i)
    d[i] = s[i];
  return true;
}
bool byte_move(void *dst, size_t cap, const void *src, size_t n) {
  if (n > cap || (n && (!dst || !src)))
    return false;
  if (!n || dst == src)
    return true;
  unsigned char *tmp = malloc(n);
  if (!tmp)
    return false;
  unsigned char *d = dst;
  const unsigned char *s = src;
  for (size_t i = 0; i < n; ++i)
    tmp[i] = s[i];
  for (size_t i = 0; i < n; ++i)
    d[i] = tmp[i];
  free(tmp);
  return true;
}
