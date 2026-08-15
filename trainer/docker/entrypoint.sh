#!/bin/sh
set -eu

exec /opt/dsa-trainer/bin/dsa-trainer "$DSA_ROOT" "$PORT" "$TRAINER_PATH" "$BIND_HOST"
