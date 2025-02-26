🐚 Custom C Shell

A simple Unix-like shell implemented in C with basic file system operations, directory management, and file manipulation commands.

📚 Table of Contents
	•	About
	•	Features
	•	Installation
	•	Usage
	•	Available Commands
	•	File Structure
	•	Known Issues
	•	Contributing
	•	Author
	•	License

🎯 About

This project is a custom shell written in C, designed to mimic basic Unix shell functionalities. It supports file operations, directory manipulation, and essential shell commands like ls, cd, cp, mv, rm, and more. The project aims to strengthen understanding of system calls, file handling, and process management in C.

✨ Features
	•	🗂️ File and Directory Management: Create, delete, and navigate directories and files.
	•	📋 File Copy and Move: Copy and move files between directories.
	•	📝 Ownership Management: Change file permissions.
	•	💡 Recursive Directory Deletion: Delete directories and their contents recursively.
	•	🔍 View Current Directory: Display the present working directory.
	•	🏃 Basic Command Execution: Execute a set of predefined commands.
	•	🎨 Screen Clearing: Clear the terminal screen with the clr command.
	•	🚪 Graceful Exit: Exit the shell cleanly.


⚡ Installation
	1.	Clone the repository:

git clone https://github.com/nasrlol/unixshell
cd unixshell 

	2.	Compile the shell:

gcc -o custom_shell main.c


	3.	Run the shell:

./custom_shell

🛠 Usage

After running the shell (./custom_shell), you can execute the following commands:

$ ls [directory]          # List files in a directory
$ mkdir [directory_name]   # Create a new directory
$ rmdir [directory_name]   # Recursively delete a directory and its contents
$ rm [file_name]           # Delete a file
$ cp [source] [destination]# Copy files from source to destination
$ mv [source] [destination]# Move files from source to destination
$ chown [file]             # Change file ownership (permission)
$ pwd                      # Print the current working directory
$ cd [directory]           # Change the working directory
$ clr                      # Clear the terminal
$ echo [message]           # Display a message
$ exit                     # Exit the shell
