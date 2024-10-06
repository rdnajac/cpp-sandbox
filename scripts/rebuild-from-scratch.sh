#!/bin/bash
# Scripting cmake
GITROOT=$(git rev-parse --show-toplevel)
(
cd $GITROOT || exit
rm -rfv build
mkdir -v build
cd build || exit
cmake ..
make
)
