# Task 5

## Overview

This project implements a minimal Unix-like shell in C with support for basic shell features. The shell follows the traditional read-eval-print loop (REPL) architecture with clear separation between tokenization, parsing, and execution phases.

## Components

### 1. Main Driver
**File:** `main.c`  
**Purpose:** Manages the shell's main loop and user interaction.  
**Key Functions:**
- `read_line()` - Reads user input with support for Ctrl+D
- `main()` - Initializes shell and runs the REPL cycle

**Interesting details:**
- Simple prompt: `$ ` without complex PS1 customization
- Handles both interactive mode and command-line arguments
- Clean resource management after each command cycle

### 2. Lexem Analyzer
**Files:** `lexer.h`, `lexer.c`  
**Purpose:** Splits input strings into tokens with quote and escape handling.  
**Key Functions:**
- `split_to_list()` - Converts string to token array
- `sub_env_vars()` - Expands environment variables
- `process_word()` - Internal helper for quote processing

**Features:**
- **Quote handling**: Single (`'`) and double (`"`) quotes with proper nesting
- **Escape sequences**: Backslash (`\`) escapes next character
- **Variable expansion**: `$HOME`, `$USER`, `$SHELL` support
- **Special characters**: Recognizes `|`, `&`, `;`, `<`, `>`, `(`, `)`
- **Comments**: Lines starting with `#` are ignored

**Technical highlights:**
- Dynamic token array that grows as needed
- Proper memory management with `strdup()` and `free()`
- State machine for parsing quotes and escape sequences
- Separate variable lookup table for built-in variables

### 3. Parser
**Files:** `tree.h`, `tree.c`  
**Purpose:** Builds an Abstract Syntax Tree (AST) from tokens.  
**Key Functions:**
- `split_tokens()` - Main parsing entry point
- `parse_pipe()` - Handles `|` operator (left-associative)
- `parse_list()` - Handles `;` sequences
- `parse_redir()` - Processes `<`, `>`, `>>` operators

**Interesting details:**
- Recursive descent parser with lookahead
- Error recovery with `err_flag` tracking
- Background flag propagation through AST nodes

### 4. Executor
**Files:** `executor.h`, `executor.c`  
**Purpose:** Executes the parsed command tree.  
**Key Functions:**
- `run_cmd()` - Dispatches based on command type
- `run_simple()` - Executes simple commands
- `run_pipe_recursive()` - Handles pipe execution
- Built-in commands: `run_cd()`, `run_pwd()`, `run_exit()`

**Features:**
- **Built-in commands**: `cd`, `pwd`, `exit` handled internally
- **External commands**: Uses `fork()` + `execvp()` for external programs
- **Pipes**: Creates pipes between processes with proper fd management
- **Redirection**: Input/output redirection via `dup2()`
- **Background jobs**: Fork without waiting, prints PID

**Technical highlights:**
- Recursive pipe execution matches AST structure
- Proper file descriptor cleanup in all execution paths
- Background process tracking (prints "[PID] started")
- Environment variable inheritance through `execvp()`
- Error reporting for "command not found" cases

