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
        cpp_content = cpp_file.read()

    markdown_content = f"# {filename}\n\n```cpp\n{cpp_content}\n```\n"

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
    if len(sys.argv) != 2:
        print(f"Usage: python {sys.argv[0]} <input_folder>")
        sys.exit(1)

    input_folder = sys.argv[1]
    process_folder(input_folder)
    print("Conversion completed.")
