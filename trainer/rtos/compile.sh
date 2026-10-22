#!/bin/sh
# Usage: sh compile.sh REPOSITORY TEST_SOURCE IMPLEMENTATION OUTPUT
set -eu
root=$1
test_source=$2
implementation=$3
output=$4
support=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
kernel="$root/third_party/freertos"
port="$kernel/portable/ThirdParty/GCC/Posix"
if [ ! -f "$kernel/include/FreeRTOS.h" ]; then
  echo "Missing pinned FreeRTOS dependency: $kernel" >&2
  exit 2
fi
exec gcc -std=c17 -D_POSIX_C_SOURCE=200809L -O0 -g -Wall -Wextra -Wpedantic -pthread \
  -I"$support" -I"$kernel/include" -I"$port" -I"$port/utils" \
  "-DDSA_IMPLEMENTATION=\"$implementation\"" "$test_source" \
  "$kernel/tasks.c" "$kernel/queue.c" "$kernel/list.c" \
  "$kernel/timers.c" "$kernel/event_groups.c" "$kernel/stream_buffer.c" \
  "$kernel/portable/MemMang/heap_3.c" "$port/port.c" "$port/utils/wait_for_event.c" \
  -o "$output"
