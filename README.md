# Tiny_FS

## Description
Tiny_FS is a partition-based file system simulator that enables file management using essential data structures such as inodes, directories, and data blocks. This project is designed to emulate basic operations of a traditional file system, allowing users to create, read, write, modify, and delete files in a controlled environment.

## Main Objective
The main goal of Tiny_FS is to provide a minimal yet functional structure for managing files and directories, using fundamental concepts such as:

### Inodes
Each file or directory is associated with an inode that stores important metadata, such as permissions, data block pointers, size, and content type.

### Directories
Directories organize and store multiple files, providing a simple and efficient hierarchy for navigating the file system.

### Data Blocks
Data blocks are the basic units for storing information in the system, managing content such as text, images, etc.

## Dependencies

### Libft Library

### Standard Libraries:

- stdio.h
- stdlib.h
- string.h
- ctype.h
- unistd.h

### Additional Libraries:

- readline/readline.h
- readline/history.h

# Use of Auxiliary Library (42 Libft)
In this project, I have incorporated my custom function library, libft, developed as part of the 42 Madrid school curriculum. The purpose of using this library is to enhance and strengthen standard functions by providing customized versions tailored specifically to the needs of this project.

Original project link: [**42_Libft**](https://github.com/ismaelucky342/Libft)

Functions used:

- `ft_memmove`: Memory copy function used as a replacement for `memcpy` to prevent overlapping issues.
- `ft_strtok`: A safe version of `strtok` that avoids modifying the original string.
- `ft_printf`: A more optimized implementation of `printf`.
- `ft_perror`: A custom version of `perror` using `write`, with personalized colors.
- `ft_strcpy` and `ft_strcmp`: Customized versions of `strcpy` and `strcmp` with additional protections.

## Cloning and Compilation

1. Clone the repository:
    
    ```bash
    git clone https://github.com/user/project.git
    ```
    
2. Makefile usage:
    
    ```bash
    make all    # Compile both the auxiliary library and the main program
    
    make        # Compile only the auxiliary library
    
    make re     # Recompile everything
    
    make fclean # Clean up object files and the executable
    ```
    
3. Running the program:
    
    ```bash
    ./tiny_fs
    ```
    

## Usage

Run `./tiny_fs` to interact with the file system. Available commands:

- `info`: Show information about the superblock.
- `print [name]`: Print the content of a file.
- `rename [old name] [new name]`: Rename a file or directory.
- `remove [name]`: Delete a file or directory.
- `copy [name] [new name]`: Copy a file or directory.
- `bytemaps`: Show information about the byte maps.
- `exit`: Exit the file system.

Additionally, the program features a functional command history, allowing users to navigate through previously used commands using the up and down arrow keys.

## Project Structure

```
less
CopyEdit
├── Libft
├── Makefile
├── README.md
├── includes
|    └── tiny_fs.h
└── src
     ├── bytemaps.c
     ├── directory.c
     ├── file_operations.c
     ├── inode.c
     ├── save_data.c
     ├── superblock.c
     └── main.c

```

## License
This project is licensed under the MIT License. See the [LICENSE](https://www.notion.so/LICENSE) file for more details.

## Extras
This project has provided an enriching experience in deepening file management knowledge within the field of operating systems. Moreover, it serves as a solid foundation for future developments and projects related to system and file management.

![image](https://github.com/ismaelucky342/U-Tad/assets/153450550/62bc16fd-1d63-401e-962d-b090cad59bdc)
