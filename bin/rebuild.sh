#!/usr/bin/env bash

set -o errexit

PARENT_DIR=$(dirname "$(readlink -f "$0")")
PROJECT_DIR=$(dirname "$PARENT_DIR")

pushd "$PROJECT_DIR"
cmake CMakeLists.txt -Bbuild
cmake --build build/
popd
