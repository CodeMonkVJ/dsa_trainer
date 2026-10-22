#!/bin/sh
set -eu

exec /opt/interview-trainer/bin/interview-trainer "$DSA_ROOT" "$PORT" "$TRAINER_PATH" "$BIND_HOST"
