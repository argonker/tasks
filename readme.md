# Task 4

A set of basic Unix-like command line utilities implemented in C.

## Overview

This project provides implementations of five fundamental command line tools:
- `echo` - display text with formatting options
- `cat` - concatenate and display files with line numbering
- `mv` - move or rename files and directories
- `cp` - copy file contents
- `cmp` - compare two files byte by byte

## Utilities

### 1. echo
**File:** `echo.c`  
**Description:** Prints command line arguments with formatting control.  
**Flags:**
- `-n` - do not output trailing newline
- `-s` - do not separate arguments with spaces

### 2. cat
**File:** `cat.c`  
**Description:** Concatenates and displays file contents.  
**Flags:**
- `-n` - number all output lines

### 3. mv
**File:** `mv.c`  
**Description:** Moves or renames files and directories.  
**Features:**
- Supports moving multiple files to a directory
- Checks file existence
- Handles move errors appropriately

### 4. cp
**File:** `cp.c`  
**Description:** Copies content from source to destination file.  
**Features:**
- Verifies source file existence
- Creates destination file if needed
- Provides copy confirmation

### 5. cmp
**File:** `cmp.c`  
**Description:** Compares two files byte by byte.  
**Features:**
- Shows first differing position (byte and line)
- Detects which file is shorter
- Returns appropriate exit codes

