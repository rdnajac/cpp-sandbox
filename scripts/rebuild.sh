#!/bin/bash
# Scripting cmake
GITROOT=$(git rev-parse --show-toplevel)
(
cd $GITROOT/build || exit
cmake ..
make
)
