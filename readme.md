# Task 7 (1)  


## Option 1 - Calculator  

A TCP client-server application implementing a calculator with a configurable increment. The server supports multiple client connections using the `fork()` mechanism.

## Key Features

- **Concurrency**: Handles multiple clients simultaneously via `fork()`
- **Signal Handling**: 
  - `SIGCHLD` – prevents zombie processes
  - `SIGPIPE` – ignored to prevent crashes when writing to closed sockets
  - `SIGINT` – graceful client shutdown
- **Commands**:
  - `\+ <number>` – set the increment value
  - `<number>` – add the current increment to the number
  - `\?` – query the current increment value
  - `\-` – close the connection


## Technologies

- **Networking**: Sockets (TCP/IP)
- **System Calls**: `fork()`, `waitpid()`, `signal()`
- **Standard Libraries**: `stdio.h`, `stdlib.h`, `string.h`, `unistd.h`, `signal.h`, `sys/socket.h`, `netinet/in.h`, `arpa/inet.h`, `sys/wait.h`

**External Dependencies**: None (uses only standard C library and POSIX system calls)  

## Usage & Commands

### Connecting to the Server

```bash

./client <host> <port>

```
## Commands

| Command | Syntax | Description |
|---------|--------|-------------|
| Add to increment | `<number>` | Adds current increment to the number |
| Set increment | `\+ <number>` | Changes the increment value |
| Get increment | `\?` | Shows current increment value |
| Exit | `\-` | Closes connection |
