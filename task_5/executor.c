#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int run_cd(char **args) {
    if (!args[1]) {
        char *home = getenv("HOME");
        if (!home) {
            fprintf(stderr, "cd: no HOME\n");
            return 1;
        }
        return chdir(home) == 0 ? 0 : 1;
    }
    return chdir(args[1]) == 0 ? 0 : 1;
}

int run_pwd(void) {
    char cwd[1024];
    return getcwd(cwd, sizeof(cwd)) ? (printf("%s\n", cwd), 0) : 1;
}

int run_exit(void) {
    exit(0);
    return 0;
}

int open_redir(const char *name, int flags, mode_t mode) {
    int fd = open(name, flags, mode);
    if (fd < 0) {
        perror(name);
        exit(1);
    }
    return fd;
}

int run_simple(Command *cmd) {
    if (cmd->argv && cmd->argv[0]) {
        if (strcmp(cmd->argv[0], "cd") == 0) 
			return run_cd(cmd->argv);
        if (strcmp(cmd->argv[0], "pwd") == 0) 
			return run_pwd();
        if (strcmp(cmd->argv[0], "exit") == 0) 
			return run_exit();
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        if (cmd->infile) {
            int fd = open_redir(cmd->infile, O_RDONLY, 0);
            dup2(fd, 0);
            close(fd);
        }
        
        if (cmd->outfile) {
            int flags = O_WRONLY | O_CREAT;
            flags |= cmd->append ? O_APPEND : O_TRUNC;
            int fd = open_redir(cmd->outfile, flags, 0644);
            dup2(fd, 1);
            close(fd);
        }
        
        execvp(cmd->argv[0], cmd->argv);
        fprintf(stderr, "%s: no such command\n", cmd->argv[0]);
        exit(127);
    }
    
    int status;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}

int run_pipe_recursive(Command *cmd) {
    int fd[2];
    
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }
    
    pid_t left_pid = fork();
    if (left_pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (left_pid == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        
        run_cmd(cmd->left);
        exit(0);
    }
    
    pid_t right_pid = fork();
    if (right_pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (right_pid == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        
        run_cmd(cmd->right);
        exit(0);
    }
    
    close(fd[0]);
    close(fd[1]);
    
    waitpid(left_pid, NULL, 0);
    waitpid(right_pid, NULL, 0);
    
    return 0;
}

int run_cmd(Command *cmd) {
    if (!cmd) return 0;
    
    switch (cmd->type) {
        case cmd_only:
            return run_simple(cmd);
            
        case cmd_pipe:
            return run_pipe_recursive(cmd);
            
        case cmd_seq:
            run_cmd(cmd->left);
            return run_cmd(cmd->right);
            
        case cmd_back:
            cmd->left->background = 1;
            return run_cmd(cmd->left);
    }
    
    return 0;
}
