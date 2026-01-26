#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char **tokens = NULL;
static int cur_pos = 0;
static int err_flag = 0;

char* cur(void) {
    return tokens ? tokens[cur_pos] : NULL;
}

void next(void) {
    if (tokens && tokens[cur_pos]) {
        cur_pos++;
    }
}

int is_spec(const char *t) {
    if (!t) return 0;
    return strchr("|&;<>()", t[0]) != NULL;
}

int is_redir(const char *t) {
    return t && (strcmp(t, "<") == 0 || strcmp(t, ">") == 0 || strcmp(t, ">>") == 0);
}

void err(const char *msg) {
    err_flag = 1;
    fprintf(stderr, "Syntax: %s\n", msg);
}

Command* make_simple(char **argv) {
    Command *cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;
    
    cmd->type = cmd_only;
    cmd->argv = argv;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->left = NULL;
    cmd->right = NULL;
    cmd->background = 0;
    
    return cmd;
}

Command* make_pipe(Command *left, Command *right) {
    Command *cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;
    
    cmd->type = cmd_pipe;
    cmd->argv = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->left = left;
    cmd->right = right;
    cmd->background = 0;
    
    return cmd;
}

Command* make_seq(Command *left, Command *right) {
    Command *cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;
    
    cmd->type = cmd_seq;
    cmd->argv = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    cmd->left = left;
    cmd->right = right;
    cmd->background = 0;
    
    return cmd;
}

void parse_redir(Command *cmd) {
    char *redir = cur();
    next();
    
    char *fname = cur();
    if (!fname || is_spec(fname)) {
        err("no file after redir");
        return;
    }
    next();
    
    if (strcmp(redir, "<") == 0) {
        if (cmd->infile) free(cmd->infile);
        cmd->infile = strdup(fname);
    }
    else if (strcmp(redir, ">") == 0) {
        if (cmd->outfile) free(cmd->outfile);
        cmd->outfile = strdup(fname);
        cmd->append = 0;
    }
    else if (strcmp(redir, ">>") == 0) {
        if (cmd->outfile) free(cmd->outfile);
        cmd->outfile = strdup(fname);
        cmd->append = 1;
    }
}

Command* parse_simple(void) {
    char *args[256];
    int cnt = 0;
    
    while (cur() && !is_spec(cur())) {
        args[cnt++] = strdup(cur());
        next();
        if (cnt >= 255) break;
    }
    
    if (cnt == 0) {
        err("no command");
        return NULL;
    }
    
    args[cnt] = NULL;
    char **argv = malloc((cnt + 1) * sizeof(char*));
    for (int i = 0; i <= cnt; i++) 
        argv[i] = args[i];
    
    Command *cmd = make_simple(argv);
    
    while (is_redir(cur())) 
        parse_redir(cmd);
    
    return cmd;
}

Command* parse_pipe(void) {
    Command *left = parse_simple();
    if (!left) return NULL;
    
    while (cur() && strcmp(cur(), "|") == 0) {
        next();
        Command *right = parse_simple();
        if (!right) {
            free_cmd(left);
            return NULL;
        }
        left = make_pipe(left, right);
    }
    
    return left;
}

Command* parse_list(void) {
    Command *left = parse_pipe();
    if (!left) return NULL;
    
    while (cur()) {
        if (strcmp(cur(), ";") == 0) {
            next();
            Command *right = parse_pipe();
            if (!right) break;
            left = make_seq(left, right);
        }
        else if (strcmp(cur(), "&") == 0) {
            next();
            left->background = 1;
            break;
        }
        else {
            break;
        }
    }
    
    return left;
}

Command* split_tokens(TokenList t) {
    tokens = t.tokens;
    cur_pos = 0;
    err_flag = 0;
    
    if (!tokens || !tokens[0]) 
        return NULL;
    
    Command *cmd = parse_list();
    
    if (!err_flag && cur()) {
        err("extra token");
        free_cmd(cmd);
        return NULL;
    }
    
    return err_flag ? NULL : cmd;
}

void free_cmd(Command *cmd) {
    if (!cmd) return;
    
    switch (cmd->type) {
        case cmd_only:
            if (cmd->argv) {
                for (int i = 0; cmd->argv[i]; i++) 
                    free(cmd->argv[i]);
                free(cmd->argv);
            }
            if (cmd->infile) free(cmd->infile);
            if (cmd->outfile) free(cmd->outfile);
            break;
            
        case cmd_pipe:
        case cmd_seq:
            free_cmd(cmd->left);
            free_cmd(cmd->right);
            break;
            
        case cmd_back:
            free_cmd(cmd->left);
            break;
    }
    
    free(cmd);
}

void show_cmd_tree(Command *cmd, int depth) {
    if (!cmd) return;
    
    for (int i = 0; i < depth; i++) 
        printf("  ");
    
    switch (cmd->type) {
        case cmd_only:
            printf("SIMPLE:");
            for (int i = 0; cmd->argv && cmd->argv[i]; i++) 
                printf(" %s", cmd->argv[i]);
            if (cmd->infile) printf(" < %s", cmd->infile);
            if (cmd->outfile) printf(" %s %s", cmd->append ? ">>" : ">", cmd->outfile);
            if (cmd->background) printf(" &");
            printf("\n");
            break;
            
        case cmd_pipe:
            printf("PIPE:\n");
            show_cmd_tree(cmd->left, depth + 1);
            printf("  |\n");
            show_cmd_tree(cmd->right, depth + 1);
            break;
            
        case cmd_seq:
            printf("SEQ:\n");
            show_cmd_tree(cmd->left, depth + 1);
            printf("  ;\n");
            show_cmd_tree(cmd->right, depth + 1);
            break;
            
        case cmd_back:
            printf("BACKGROUND:\n");
            show_cmd_tree(cmd->left, depth + 1);
            printf("  &\n");
            break;
    }
}
