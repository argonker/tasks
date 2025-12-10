# Task 4

## Overview

This project provides implementations of five fundamental command line tools with clean, efficient C code. Each utility demonstrates practical file I/O operations and command-line argument parsing.

## Utilities

### 1. echo
**File:** `echo.c`  
**Description:** Prints command line arguments with formatting control.  
**Flags:**
- `-n` - do not output trailing newline
- `-s` - do not separate arguments with spaces

**Interesting detail:** Uses a clever boolean condition in printf: `printf((No_Separations)?"%s":"%s ", argv[i])` to toggle space insertion without extra branching.

### 2. cat
**File:** `cat.c`  
**Description:** Concatenates and displays file contents.  
**Flags:**
- `-n` - number all output lines

**Interesting details:**
- Line numbers are right-aligned to 6 spaces: `printf("%6d  ", line_num)`
- Uses low-level file descriptors (`open()`, `read()`) instead of `FILE*` streams
- Tracks newline state with a simple boolean flag: `newline = (chr == '\n')`

### 3. ls
**File:** `ls.c`  
**Description:** Lists directory contents with various display options.  
**Flags:**
- `-l` - use a long listing format
- `-R` - list subdirectories recursively
- `-g` - like -l, but do not list owner

**Features:**
- Intelligent argument handling (files vs directories)
- Recursive directory traversal with proper header formatting
- Permission and file type display
- Special device file support (major/minor numbers)
- Hidden file filtering (skips files starting with '.')

**Technical highlights:**
- Dual-pass directory reading for recursive mode (read for display, then read for recursion)
- Proper use of `lstat()` vs `stat()` for symbolic link handling
- Structured error reporting with perror for system call failures
- Memory-efficient path construction using fixed-size buffers

### 4. mv
**File:** `mv.c`  
**Description:** Moves or renames files and directories.  
**Features:**
- Smart directory detection using `stat()` and `S_ISDIR()`
- Automatic basename extraction: `strrchr(argv[i], '/')`
- Batch file moving support

**Interesting details:**
- Checks for self-move: `if (!strcmp(argv[1], argv[2]))`
- Uses `rename()` system call for atomic file operations
- Handles both single file rename and multiple file moves to directory

### 5. pwd
**File:** `pwd.c`  
**Description:** Prints the current/working directory.  
**Features:**
- Simple one-liner implementation
- Memory-safe with proper allocation and freeing
- Cross-platform compatible

**Interesting details:**
- Uses `getcwd(NULL, 0)` for automatic buffer allocation
- Always includes trailing newline for clean output
- Proper memory management: `free(cwd)` after use

### 6. cmp
**File:** `cmp.c`  
**Description:** Compares two files byte by byte.  
**Features:**
- Shows first differing position (byte and line)
- Detects EOF differences
- Tracks both byte and line positions

**Interesting details:**
- Single-byte reads for precise comparison: `read(fd1, &byte1, 1)`
- Dual file descriptor handling with proper cleanup
- Line tracking resets on `'\n'`: `if (byte1 == '\n') { line++; byte = 1; }`

