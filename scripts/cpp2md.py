#! /usr/bin/env python3
import os
import sys
import subprocess


def get_repo_root() -> str:
    """
    Get the root directory of the git repository.

    Returns:
    str: The path to the root of the git repository.
    """
    try:
        repo_root = subprocess.check_output(
            ["git", "rev-parse", "--show-toplevel"], universal_newlines=True
        ).strip()
        return repo_root
    except subprocess.CalledProcessError:
        print("Error: This script must be run from within a git repository.")
        sys.exit(1)


REPO_ROOT = get_repo_root()
DOCSDIR = os.path.join(REPO_ROOT, "docs")


def to_title(filename: str) -> str:
    """
    Convert a filename to a title.
    2-5_consecutive_character_groups.cpp -> Consecutive Character Groups
    Drop the prefix, extension, replace underscores with spaces, and title-case the words.

    Args:
    filename (str): The filename to be converted.

    Returns:
    str: The title derived from the filename.
    """
    # Drop the extension
    filename = os.path.splitext(filename)[0]

    # Find the start of the title by skipping over non-alpha characters
    start = 0
    while start < len(filename) and not filename[start].isalpha():
        start += 1

    # Replace underscores with spaces and capitalize words
    title = " ".join(word.capitalize() for word in filename[start:].split("_"))
    return title


def test_to_title():
    CASES = [
        ("2-5_consecutive_character_groups.cpp", "Consecutive Character Groups"),
        ("containers.cpp", "Containers"),
        ("123_example_file.txt", "Example File"),
        ("--another_example.cpp", "Another Example"),
    ]
    for filename, expected in CASES:
        assert to_title(filename) == expected
    print("to_title passed")


def create_markdown_file(cpp_file_path: str, output_folder: str) -> None:
    """
    Convert a C++ file to a Markdown file and save it in the specified output folder.

    Args:
    cpp_file_path (str): Path to the C++ file to be converted.
    output_folder (str): Path to the folder where the Markdown file will be saved.
    """
    filename = os.path.splitext(os.path.basename(cpp_file_path))[0]
    os.makedirs(output_folder, exist_ok=True)
    output_file_path = os.path.join(output_folder, f"{filename}.md")

    with open(cpp_file_path, "r") as cpp_file:
        source_code = cpp_file.read()

    markdown_content = f"# {to_title(filename)}\n\n```cpp\n{source_code}\n```\n"

    with open(output_file_path, "w") as md_file:
        md_file.write(markdown_content)

    print(f"Created: {output_file_path}")


def process_folder(input_folder: str) -> None:
    """
    Process all C++ files in the input folder and its subfolders, converting them to Markdown.

    Args:
    input_folder (str): Path to the folder containing C++ files to be converted.
    """
    for root, _, files in os.walk(input_folder):
        for file in files:
            if file.endswith(".cpp"):
                cpp_file_path = os.path.join(root, file)
                parent_folder = os.path.basename(os.path.dirname(cpp_file_path))
                output_folder = os.path.join(DOCSDIR, parent_folder)
                create_markdown_file(cpp_file_path, output_folder)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: python {sys.argv[0]} <input_folder1> [<input_folder2> ...]")
        sys.exit(1)

    # If the first argument is --test
    if sys.argv[1] == "--test":
        test_to_title()
        sys.exit(0)

    # Process each input folder provided
    for input_folder in sys.argv[1:]:
        process_folder(input_folder)

    print("Conversion completed.")
