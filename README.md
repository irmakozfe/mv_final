# Move Command Implementation in C

##  Introduction
This project is a **C-based implementation** of the `mv` (move) command. It is developed as part of the **System-Oriented Programming Portfolio Assignment 05** and demonstrates various skills in **C programming**, including interaction with the Linux filesystem, dynamic memory management, and multithreading.

---
## Features

-Filesystem Interaction: Recursively traverses directories to display their structure.
-Command-line Options: Supports flags to customize output (e.g., -L to limit depth).
-Dynamic Data Structures: Uses linked lists and trees to manage directory entries.
-Concurrency: Implements multithreading to traverse multiple directories simultaneously and build tree structure for json and csv format.
-Pipeline Support: Integrates with Linux pipelines via stdin and stdout.
-Thread Safety: Ensures safe access to shared resources using mutexes.

**File and Directory Operations**  
   - Move **single** or **multiple** files and directories.  
   - Overwrite existing files based on user preferences.  
   - Create **backup** files before overwriting (`-b`).  
   - Move directories recursively (`-r`).  
   - Handle **symbolic links** (`-l`).  
**Command-Line Options**  
   - `-f`: **Force move** (overwrite without asking).  
   - `-i`: **Interactive mode** (asks before overwriting).  
   - `-n`: **No clobber** (prevents overwriting).  
   - `-b`: **Backup** existing file before moving.  
   - `-v`: **Verbose mode** (displays actions performed).  
   - `--help`: Shows **usage information**.  
**Error Handling**  
   - Handles **invalid file paths**, **missing permissions**, and **operation failures**.  
   - Provides **clear error messages**.  
**Memory Management**  
   - **Proper allocation and deallocation** to prevent **memory leaks**.  
**Thread Safety (optional)**  
   - Mutex protection for shared resources (if extended to support parallel processing).  
 **Pipeline Integration**  
   - Can be used in **shell scripting** and **piped with other commands**.

---

## Requirements
To build and run the project, **ensure the following dependencies** are installed:

- **Make Utility** (`make --version`)
- **Git (optional, for version control)**


## Build & Run Instructions

###  Clone the Repository
```bash
git clone https://github.com/bussyyr/mv_command.git
cd mv_command
```

###  Compile the Project
Use the provided **Makefile**:
```bash
make all
```
This will generate an **`mv` executable** inside the project directory.

###  Run the Program
Basic syntax:
```bash
./mv [options] [source] [destination]
```

####  **Examples**
**Move a file to a new location:**
   ```bash
   ./mv file1.txt /destination/folder/
   ```
**Move multiple files:**
   ```bash
   ./mv file1.txt file2.txt /destination/folder/
   ```
**Move a directory to a new location:**
   ```bash
   ./mv directory /destination/folder/
   ```
**Move multiple directories to a new location:**
   ```bash
   ./mv directory1 directory2 /destination/folder/
   ```
**Rename a file:**
   ```bash
   ./mv file1.txt new_file_name.txt
   ```
**Rename a directory.**
   ```bash
   ./mv directory new_directory_name
   ```
**Force move without confirmation:**
   ```bash
   ./mv -f file1.txt /destination/folder/
   ```
 **Backup before moving:**
   ```bash
   ./mv -b file1.txt /destination/folder/
   ```
 **Interactive move (asks before overwriting):**
   ```bash
   ./mv -i file1.txt /destination/folder/
   ```
**Prevent overwriting existing files (-n no clobber mode):**
  ```bash
   ./mv -n file1.txt /destination/folder/
   ```
**Verbose mode (show actions performed):**
  ```bash
   ./mv -v file1.txt /destination/folder/
   ```
**Display help message:**
  ```bash
   ./mv --help
   ```
---

##  Command-Line Options
| Option | Description |
|--------|-------------|
| `-f` | Force move (overwrite without confirmation) |
| `-i` | Interactive mode (ask before overwriting) |
| `-n` | No clobber (do not overwrite existing files) |
| `-b` | Backup before overwriting |
| `-v` | Verbose mode (display move details) |
| `--help` | Show usage information |
---

## **Cleaning the Build**
To remove compiled files and **reset the project**:
```bash
make clean
```

---

## Error Handling
If any errors occur, the program provides **clear messages**.  
Examples:
- **File does not exist:**
  ```bash
  Error: Source file 'file1.txt' does not exist.
  ```
- **Permission denied:**
  ```bash
  Error: Permission denied.
  ```
- **Invalid command:**
  ```bash
  usage: ./mv [-f | -i | -n] [-hv] source target
         ./mv [-f | -i | -n] [-v] source ... directory
  ```

---

## Contributors
- [Buse Okcu](https://github.com/bussyyr)
- [Irmak Damla Özdemir](https://github.com/irmakozfe)
- [Nihal Beyza Dogan](https://github.com/nihalbeyzadogan)

---
