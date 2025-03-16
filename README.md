# Custom C Shell

A simple Unix-like shell implemented in C with basic file system operations, directory management, and file manipulation commands.

## Table of Contents
- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Available Commands](#available-commands)
- [File Structure](#file-structure)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [Author](#author)
- [License](#license)

## About

This project is a custom shell written in C, designed to mimic basic Unix shell functionalities. It supports file operations, directory manipulation, and essential shell commands like `ls`, `cd`, `cp`, `mv`, `rm`, and more.  

The goal of this project is to enhance understanding of:
- System calls
- File handling
- Process management in C

## Features

- **File and Directory Management** – Create, delete, and navigate directories and files.
- **File Copy and Move** – Copy and move files between directories.
- **Ownership Management** – Change file permissions.
- **Recursive Directory Deletion** – Delete directories and their contents recursively.
- **View Current Directory** – Display the present working directory.
- **Basic Command Execution** – Execute a set of predefined commands.
- **Screen Clearing** – Clear the terminal screen with the `clr` command.
- **Graceful Exit** – Exit the shell cleanly.

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/nasrlol/unixshell
   cd unixshell
   ```

2. Compile the shell:
   ```sh
   gcc -o custom_shell main.c
   ```

3. Run the shell:
   ```sh
   ./custom_shell
   ```

## Usage

After running the shell (`./custom_shell`), you can execute the following commands:

### Available Commands

| Command                      | Description                                      |
|------------------------------|--------------------------------------------------|
| `ls [directory]`             | List files in a directory                        |
| `mkdir [directory_name]`     | Create a new directory                           |
| `rmdir [directory_name]`     | Recursively delete a directory and its contents |
| `rm [file_name]`             | Delete a file                                   |
| `cp [source] [destination]`  | Copy files from source to destination           |
| `mv [source] [destination]`  | Move files from source to destination           |
| `chown [file]`               | Change file ownership (permissions)             |
| `pwd`                        | Print the current working directory             |
| `cd [directory]`             | Change the working directory                    |
| `clr`                        | Clear the terminal                              |
| `echo [message]`             | Display a message                               |
| `exit`                       | Exit the shell                                  |

## File Structure

```
 unixshell
 ├── main.c          # Main source file for the shell
 ├── shell.h         # Header file (definitions & prototypes)
 ├── commands.c      # Functions handling shell commands
 ├── utils.c         # Utility functions
 ├── README.md       # Documentation
 ├── LICENSE         # License information
```

## Known Issues

- Some commands may not fully replicate the behavior of a standard Unix shell.
- Does not support piping (`|`) and complex command chaining.

## Contributing

Contributions are welcome! If you’d like to improve this project, follow these steps:

1. Fork the repository
2. Create a new branch
3. Make your changes and test them
4. Submit a pull request

## Author

**Appie (nasrlol)**  
- GitHub: [@nasrlol](https://github.com/nasrlol)  
- Website: [nasrlol.dev](https://nasrlol.dev)  

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.
