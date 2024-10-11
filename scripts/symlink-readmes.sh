#!/bin/bash
## Create symlinks for READMEs in the docs directory
#
# This script navigates to the docs directory and creates symlinks for:
# 1. The main README.md as index.md
# 2. Other README.md files in the src directory, using the parent folder's name for the symlink.
# 3. README.md files in the projects directory, also using the parent folder's name.

# Navigate to the docs directory
cd docs || exit

# Create a symlink for the main README.md
ln -sf ../README.md index.md

# Function to create symlinks for README.md files
create_symlinks() {
	local base_dir="$1"
	local output_dir="$2"

	mkdir -p "$output_dir"

	for readme in "$base_dir"/*/README.md; do
		if [ -f "$readme" ]; then
			dir=$(dirname "$readme")
			parent_folder=$(basename "$dir")
			link_name="${parent_folder}.md"  # Use the parent folder name as-is
			ln -sf "$readme" "${output_dir}/${link_name}"
		fi
	done
}

# Create symlinks for other READMEs in src
create_symlinks "../src" "."

# Create symlinks for project files
create_symlinks "../projects" "projects"

