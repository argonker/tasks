#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char **old_list = NULL;
int old_size = 0;
int old_pos = 0;

TokenList* make_token_list(void) {
    TokenList *list = malloc(sizeof(TokenList));
    if (!list) return NULL;
    
    list->cap = 16;
    list->cnt = 0;
    list->tokens = malloc(list->cap * sizeof(char*));
    
    if (!list->tokens) {
        free(list);
        return NULL;
    }
    
    return list;
}

void free_token_list(TokenList *list) {
    if (!list) return;
    
    for (int i = 0; i < list->cnt; i++) 
        free(list->tokens[i]);
    
    free(list->tokens);
    free(list);
}

void clear_token_list(TokenList *list) {
    if (!list) return;
    
    for (int i = 0; i < list->cnt; i++) {
        free(list->tokens[i]);
        list->tokens[i] = NULL;
    }
    
    list->cnt = 0;
}

int add_token(TokenList *list, const char *token) {
    if (!list || !token) return -1;
    
    if (list->cnt >= list->cap - 1) {
        int new_cap = list->cap * 2;
        char **new_tokens = realloc(list->tokens, new_cap * sizeof(char*));
        
        if (!new_tokens) return -1;
        
        list->tokens = new_tokens;
        list->cap = new_cap;
    }
    
    list->tokens[list->cnt] = strdup(token);
    if (!list->tokens[list->cnt]) return -1;
    
    list->cnt++;
    list->tokens[list->cnt] = NULL;
    
    return 0;
}

int token_cnt(const TokenList *list) {
    return list ? list->cnt : 0;
}

char** token_arr(const TokenList *list) {
    return list ? list->tokens : NULL;
}

char* get_var(const char *name) {
    if (strcmp(name, "HOME") == 0) {
        char *home = getenv("HOME");
        return home ? home : "";
    }
    else if (strcmp(name, "USER") == 0) {
        char *user = getenv("USER");
        return user ? user : "";
    }
    else if (strcmp(name, "SHELL") == 0) {
        char *shell = getenv("SHELL");
        return shell ? shell : "";
    }
    return getenv(name);
}

void replace_var(char **token) {
    char *t = *token;
    if (!t || t[0] != '$') return;
    
    char *var = t + 1;
    if (var[0] == '\0') return;
    
    char *val = get_var(var);
    if (val) {
        free(*token);
        *token = strdup(val);
    }
}

void sub_env_vars(TokenList *list) {
    if (!list) return;
    
    for (int i = 0; i < list->cnt; i++) 
        replace_var(&list->tokens[i]);
}

void process_word(const char *line, int start, int end, TokenList *list) {
    char *word = strndup(line + start, end - start);
    if (!word) return;
    
    char *dst = word;
    char *src = word;
    int esc = 0;
    int in_quote = 0;
    char quote = 0;
    
    while (*src) {
        if (!esc && !in_quote && (*src == '\'' || *src == '"')) {
            in_quote = 1;
            quote = *src;
            src++;
            continue;
        }
        
        if (!esc && in_quote && *src == quote) {
            in_quote = 0;
            src++;
            continue;
        }
        
        if (!esc && *src == '\\') {
            esc = 1;
            src++;
            continue;
        }
        
        esc = 0;
        *dst++ = *src++;
    }
    *dst = '\0';
    
    add_token(list, word);
    free(word);
}

TokenList* split_to_list(const char *line) {
    TokenList *list = make_token_list();
    if (!list || !line || !*line) return list;
    
    int len = strlen(line);
    int i = 0;
    
    while (i < len) {
        while (i < len && isspace(line[i])) i++;
        if (i >= len) break;
        
        if (line[i] == '#') break;
        
        if (strchr("|&;<>()", line[i])) {
            char tok[3] = {0};
            tok[0] = line[i];
            
            if (i + 1 < len && ((line[i] == '|' && line[i+1] == '|') || (line[i] == '&' && line[i+1] == '&') 
								|| (line[i] == '>' && line[i+1] == '>'))) {
                tok[1] = line[i+1];
                i += 2;
            } else 
                i++;
            
            add_token(list, tok);
            continue;
        }
        
        int start = i;
        int in_quote = 0;
        char quote = 0;
        int esc = 0;
        
        while (i < len) {
            char c = line[i];
            
            if (esc) {
                esc = 0;
                i++;
                continue;
            }
            
            if (c == '\\') {
                esc = 1;
                i++;
                continue;
            }
            
            if (!in_quote && (c == '\'' || c == '"')) {
                in_quote = 1;
                quote = c;
                i++;
                continue;
            }
            
            if (in_quote && c == quote) {
                in_quote = 0;
                i++;
                continue;
            }
            
            if (!in_quote && (isspace(c) || strchr("|&;<>()#", c))) {
                break;
            }
            
            i++;
        }
        
        if (i > start) 
            process_word(line, start, i, list);
    }
    
    return list;
}

void list_start(void) {
    old_list = NULL;
    old_size = 0;
    old_pos = 0;
}

void list_end(void) {
    for (int i = 0; i < old_pos; i++) 
        free(old_list[i]);
    
    free(old_list);
    old_list = NULL;
    old_size = 0;
    old_pos = 0;
}

TokenList split_line(const char *line) {
    TokenList *list = split_to_list(line);
    if (!list) {
        TokenList empty = {NULL, 0, 0};
        return empty;
    }
    
    TokenList result = *list;
    free(list);
    return result;
}

void sub_env(TokenList tokens) {
    TokenList temp = {tokens.tokens, tokens.cnt, tokens.cap};
    sub_env_vars(&temp);
}

void free_toks(TokenList tokens) {
    for (int i = 0; i < tokens.cnt; i++) 
        free(tokens.tokens[i]);
    
    free(tokens.tokens);
}
