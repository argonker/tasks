#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

char* read_input(void) {
    static char buf[4096];
    
    printf("[argonker_shell]$ ");
    fflush(stdout);
    
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        if (feof(stdin)) {
            printf("\n");
            return NULL;
        }
        return NULL;
    }
    
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') 
        buf[len-1] = '\0';
    
    return buf;
}

int main(int argc, char **argv) {    
    if (argc > 1) {
        char cmd[4096] = "";
        for (int i = 1; i < argc; i++) {
            strcat(cmd, argv[i]);
            strcat(cmd, " ");
        }
        
        TokenList *list = split_to_list(cmd);
        if (list) {
            sub_env_vars(list);
            
            TokenList tl = {list->tokens, list->cnt, list->cap};
            Command *tree = split_tokens(tl);
            
            if (tree) {
                run_cmd(tree);
                free_cmd(tree);
            }
            
            for (int i = 0; i < list->cnt; i++) 
                free(list->tokens[i]);
            free(list->tokens);
            free(list);
        }
        return 0;
    }
    
    while (1) {
        char *line = read_input();
        if (!line) break;
        
        if (strlen(line) == 0) continue;
        
        TokenList *list = split_to_list(line);
        if (!list) continue;
        
        sub_env_vars(list);
        
        TokenList tl = {list->tokens, list->cnt, list->cap};
        Command *cmd = split_tokens(tl);
        
        if (cmd) {
            run_cmd(cmd);
            free_cmd(cmd);
        }
        
        for (int i = 0; i < list->cnt; i++) 
            free(list->tokens[i]);
        free(list->tokens);
        free(list);
    }
    return 0;
}
