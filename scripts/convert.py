import os
import sys

def create_markdown_file(cpp_file_path, output_folder):
    # Extract the filename without extension
    filename = os.path.splitext(os.path.basename(cpp_file_path))[0]
    
    # Create the output folder if it doesn't exist
    os.makedirs(output_folder, exist_ok=True)
    
    # Create the output file path
    output_file_path = os.path.join(output_folder, f"{filename}.md")
    
    # Read the content of the C++ file
    with open(cpp_file_path, 'r') as cpp_file:
        cpp_content = cpp_file.read()
    
    # Create the markdown content
    markdown_content = f"# {filename}\n\n```cpp\n{cpp_content}\n```\n"
    
    # Write the markdown content to the output file
    with open(output_file_path, 'w') as md_file:
        md_file.write(markdown_content)
    
    print(f"Created: {output_file_path}")

def process_folder(input_folder, output_base_folder):
    for root, _, files in os.walk(input_folder):
        for file in files:
            if file.endswith('.cpp'):
                cpp_file_path = os.path.join(root, file)
                relative_path = os.path.relpath(root, input_folder)
                output_folder = os.path.join(output_base_folder, 'docs', 'code', relative_path)
                create_markdown_file(cpp_file_path, output_folder)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <input_folder> <output_base_folder>")
        sys.exit(1)
    
    input_folder = sys.argv[1]
    output_base_folder = sys.argv[2]
    
    process_folder(input_folder, output_base_folder)
    print("Conversion completed.")
