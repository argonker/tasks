# Task 7(1) (Calculator 1)

A simple TCP-based calculator application written in C. The server supports multiple concurrent clients using `fork()`, and each client session maintains its own independent increment value.

## Overview

- **Protocol:** TCP/IP (IPv4)
- **Concurrency:** Multi-process (one child process per client)
- **Default Port:** `8888`
- **Key Feature:** Full signal handling (`SIGINT`, `SIGTSTP`, `SIGCONT`, `SIGCHLD`) for graceful shutdown and process control.

### Supported Commands
| Command | Description |
|---------|-------------|
| `\+ <num>` | Set the increment value |
| `<num>` | Add the current increment to the number |
| `\?` | Show current increment value |
| `\-` | Close connection and exit |

---

## File Breakdown

### `server.c`
Handles incoming connections and business logic.

- **`sig_chld_handler`**: Reaps zombie processes using `waitpid(..., WNOHANG)` when a client disconnects.
- **`sig_term_handler`**: Catches `SIGINT`/`SIGTERM` to close the server socket gracefully.
- **`sig_tstp_handler` / `sig_cont_handler`**: Allows suspending (`Ctrl+Z`) and resuming (`fg`) the server process.
- **`client_func`**: Runs in a child process. Maintains the local `inc` state for that specific client and processes commands.
- **`main`**: Initializes the socket, binds to port, and runs the `accept()` → `fork()` loop.

### `client.c`
Interactive command-line interface for the user.

- **`sig_int_handler`**: Catches `SIGINT` (`Ctrl+C`) to close the socket before exiting.
- **`sig_tstp_handler` / `sig_cont_handler`**: Allows suspending and resuming the client process.
- **`main`**: 
  - Parses host/port arguments.
  - Establishes TCP connection.
  - Runs an interactive loop: reads stdin → sends to server → prints response.

---

## Running  

Server: ./server
Client: ./client <host> <port>  

---
