#!/bin/bash
## Create symlinks for READMEs in the docs directory
#
# Navigate to the docs directory
cd docs || exit

# Create a symlink for the main README.md
ln -sf ../README.md index.md

# Create symlinks for other READMEs
for readme in ../src/*/README.md; do
  if [ -f "$readme" ]; then
    dir=$(dirname "$readme")
    rel_path=${dir#../}
    link_name=$(echo "$rel_path" | tr '/' '_' | tr '[:upper:]' '[:lower:]').md
    ln -sf "$readme" "$link_name"
  fi
done

# Add project files
mkdir -p projects
for readme in ../projects/*/README.md; do
  if [ -f "$readme" ]; then
    dir=$(dirname "$readme")
    rel_path=${dir#../}
    link_name=$(echo "$rel_path" | tr '/' '_' | tr '[:upper:]' '[:lower:]').md
    ln -sf "$readme" "projects/${link_name}"
  fi
done
