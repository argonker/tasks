#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUF 1024
#define PORT 8888
#define CMD_LEN 2

int server_fd;

void sig_chld_handler(int s) {
    int saved_errno = errno;
    
    while (waitpid(-1, NULL, WNOHANG) > 0);
    
    errno = saved_errno;
}

void sig_term_handler(int s) {

    printf("\n### Server is shutting down, thanks to everyone\n");
    
    if (server_fd > 0) {
        close(server_fd);
    }
    
    exit(0);
}

void sig_tstp_handler(int s) {

    printf("\n*** Server suspended. Use 'fg' to resume.\n");
    raise(SIGSTOP);
}

void sig_cont_handler(int s) {

    printf("\n*** Server resumed.\n");
}

void client_func(int client_fd) {
    char buf[MAX_BUF];
    int inc = 1; 
    int n;
    char *str;
    char *fin = "Closing calculator, goodbye!";
    char *chg = "Increment is changed";
    
    while (1) {
        memset(buf, 0, MAX_BUF);
        n = read(client_fd, buf, MAX_BUF - 1);
        if (n <= 0) {
            break;
        }
        
        str = buf;
        while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n') str++;
        
        char *str_end = str + strlen(str) - 1;
        while (str_end > str && (*str_end == ' ' || *str_end == '\t' || *str_end == '\r' || *str_end == '\n')) {
            *str_end = '\0';
            str_end--;
        }
        
        if (strlen(str) == 0) {
            continue;
        }
        
        if (strcmp(str, "\\?") == 0) {
            char res[128];
            snprintf(res, sizeof(res), "%d", inc);
            write(client_fd, res, strlen(res));
        }

        else if (strcmp(str, "\\-") == 0) {
            write(client_fd, fin, strlen(fin));
            break;
        }

        else if (strncmp(str, "\\+", CMD_LEN) == 0) {
            char *cmd = str + CMD_LEN;
            
			while (*cmd == ' ' || *cmd == '\t') cmd++;
            
            if (*cmd >= '0' && *cmd <= '9') {
                inc = atoi(cmd);
                write(client_fd, chg, strlen(chg));
            } else {
                write(client_fd, "Invalid number", 14);
            }
        }
        
		else {
            char *endptr;
            long val = strtol(str, &endptr, 10);
            
            if (*endptr != '\0') {
                write(client_fd, "Invalid command", 15);
            } else {
                char res[64];
                snprintf(res, sizeof(res), "%ld", val + inc);
                write(client_fd, res, strlen(res));
            }
        }
    }
    
    close(client_fd);
    exit(0);
}

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    
    signal(SIGCHLD, sig_chld_handler);
    signal(SIGPIPE, SIG_IGN);
	signal(SIGINT,sig_term_handler);
	signal(SIGTERM, sig_term_handler);
	signal(SIGTSTP, sig_tstp_handler);
	signal(SIGCONT, sig_cont_handler);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        exit(1);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error while binding");
        close(server_fd);
        exit(1);
    }
    
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        exit(1);
    }
    
    printf("### Server started. Port: %d\n### Waiting for connections...\n", PORT);
    
    while (1) {
        client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("Error while accepting connection");
            continue;
        }
        
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("### New connection established. Address: %s:%d\n", 
               client_ip, ntohs(client_addr.sin_port));
        
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error in fork");
            close(client_fd);
        } else if (pid == 0) {
            close(server_fd);
            client_func(client_fd);
            exit(0);
        } else {
            close(client_fd);
        }
    }
    
    close(server_fd);
    return 0;
}
