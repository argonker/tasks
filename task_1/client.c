#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_BUF 1024

void sigint_handler(int sig) {
    (void)sig;
    printf("\nReceived SIGINT. Exiting...\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buf[MAX_BUF], res[MAX_BUF];
    char *host;
    int port;
    
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(1);
    }
    
    signal(SIGINT, sigint_handler);
    
    host = argv[1];
    port = atoi(argv[2]);
    
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port number\n");
        exit(1);
    }
    
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Error while creating socket");
        exit(1);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
            fprintf(stderr, "Unknown host: %s\n", host);
            close(sock_fd);
            exit(1);
        }
    
    if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock_fd);
        exit(1);
    }
    
    printf("Commands: \\+ <num> (set inc), <num> (add inc), \\? (get inc), \\- (exit)\n");
    
    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (!fgets(buf, MAX_BUF, stdin)) break;
        
        buf[strcspn(buf, "\r\n")] = 0;
        
        char *cmd = buf;
        while (*cmd == ' ' || *cmd == '\t') cmd++;
        
        if (strlen(cmd) == 0) continue;
        
        if (write(sock_fd, cmd, strlen(cmd)) < 0) {
            perror("write");
            break;
        }
        
        memset(res, 0, MAX_BUF);
        int n = read(sock_fd, res, MAX_BUF - 1);
        if (n <= 0) {
            printf("Server closed connection.\n");
            break;
        }
        
        printf(">>> %s\n", res);
        
        if (strcmp(cmd, "\\-") == 0 || strcmp(cmd, "\\–") == 0) {
            break;
        }
    }
    
    close(sock_fd);
    printf("Connection closed.\n");
    return 0;
}
