#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

char **lst = NULL;
char *buf = NULL;
char str[BUFFER_SIZE];
int c;
int sizebuf = 0;
int sizelist = 0;
int curbuf = 0;
int curlist = 0;
int str_pos = 0;
int str_len = 0;
int is_eof = 0;

vertex v = Start;

void clearlist() {
    int i;
    if (lst == NULL) return;
    
    for (i = 0; i < curlist; i++) 
        free(lst[i]);

    free(lst);
    
    if (buf != NULL) 
        free(buf);
    
    lst = NULL;
    buf = NULL;
    sizelist = 0;
    curlist = 0;
    sizebuf = 0;
    curbuf = 0;
    str_pos = 0;
    str_len = 0;
    is_eof = 0;
    v = Start;
}

void termlist() {
    if (lst == NULL || curlist == 0) return;
    
    char **temp = realloc(lst, (curlist + 1) * sizeof(*lst));
    if (temp != NULL) {
        lst = temp;
        lst[curlist] = NULL;
        sizelist = curlist + 1;
    }
}

void nullbuf() {
    if (buf != NULL) {
        free(buf);
    }
    buf = malloc(SIZE * sizeof(char));
    if (buf != NULL) {
        sizebuf = SIZE;
    } else {
        sizebuf = 0;
    }
    curbuf = 0;
}

void addsym() {
    if (buf == NULL) nullbuf();
    if (buf == NULL) return;
    
    if (curbuf >= sizebuf - 1) {
        char *temp = realloc(buf, sizebuf + SIZE);
        if (temp != NULL) {
            buf = temp;
            sizebuf += SIZE;
        } else 
            return;
    }
    buf[curbuf++] = c;
}

void addword() {
    if (buf == NULL || curbuf == 0) return;
    
    if (curbuf >= sizebuf - 1) {
        char *temp = realloc(buf, sizebuf + 1);
        if (temp != NULL) {
            buf = temp;
            sizebuf += 1;
        }
    }
    buf[curbuf++] = '\0';
    
    if (curlist >= sizelist) {
        char **temp = realloc(lst, (sizelist + SIZE) * sizeof(*lst));
        if (temp != NULL) {
            lst = temp;
            sizelist += SIZE;
        } else 
            return;
    }
    
    lst[curlist++] = buf;
    buf = NULL;
    sizebuf = 0;
    curbuf = 0;
}

void printlist() {
    int i;
    
    if (lst == NULL || curlist == 0) 
        return;
    
    printf("%d words\n", curlist);
	for (i = 0; i < curlist; i++) {
        printf("%s\n", lst[i]);
    }
}

void read_block() {
    if (is_eof) return;
    
    if (fgets(str, BUFFER_SIZE, stdin) != NULL) {
		str_len = strlen(str);
    	str_pos = 0;
	} else {
		is_eof = 1;
		str_len = 0;
	}
 
}

int getsym() {
    if (str_pos >= str_len) {
        read_block();
        if (str_len == 0) 
			return EOF;
    }
    
    return (char)str[str_pos++];
}

int is_letter(int ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int is_digit(int ch) {
    return ch >= '0' && ch <= '9';
}

int is_word_char(int ch) {
    return is_letter(ch) || is_digit(ch) || ch == '$' || ch == '.' || ch == '/' || ch == '_';
}

int is_special_char(int ch) {
    return ch == '|' || ch == '&' || ch == ';' || ch == '>' || ch == '<' || ch == '(' || ch == ')';
}

int is_space_char(int ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

void start() {
    if (c == EOF) {
		addword(); 
        v = Stop;
    } else if (is_space_char(c)) 
        v = Start;
    else if (is_special_char(c)) {
        nullbuf();
        addsym();
        v = Special;
    } else {
        nullbuf();
        addsym();
        v = Word;
    }
}

void word() {
    if (c == EOF || is_space_char(c)) {
        addword();
        v = Start;
    } else if (is_special_char(c)) {
        addword();
        nullbuf();
        addsym();
        v = Special;
    } else {
        addsym();
        v = Word;
    }
}

void special() {
	if (c == EOF) {
		addword();
		v = Stop;
		return;
	} 
	
	if ((buf[0] == '&' && c == '&') || (buf[0] == '>' && c == '>') || (buf[0] == '|' && c == '|')) {
        addsym(); 
       	addword();
       	v = Start;
	} else {
		addword();

		if (is_special_char(c)) {
			nullbuf();
			addsym();
			v = Special;
		} else {
			v = Start;
			start();
		}
	}
}

void newline() {
    if (c == EOF) 
        v = Stop;
    else if (is_space_char(c)) {
		if (buf == NULL)
			v = Start;
		else { 
			addword();
        	v = Start;
		}
    } else {
        v = Start;
    }
}

void sortlist() {
    if (lst == NULL || curlist < 2) return;
    
    int i, j;
    char *temp;
    
    for (i = 0; i < curlist - 1; i++) {
        for (j = 0; j < curlist - i - 1; j++) 
            if (strcmp(lst[j], lst[j + 1]) > 0) {
                temp = lst[j];
                lst[j] = lst[j + 1];
                lst[j + 1] = temp;
            }
    }
}

void double_list() {
	int i, cnt;
	char *word;
	
	if (lst == NULL) 
		return;

	cnt = 0;
	for (i = 0; i < curlist; i += 2) 
		if (i % 2 == 0)
			cnt++; 
	
	char **doubled_list = malloc((curlist + cnt) * sizeof(char*));
	int double_idx = 0;
		
	for (i = 0; i < curlist; i++) {
		doubled_list[double_idx++] = lst[i];
		if (i % 2 == 0) {
			int double_len = strlen(lst[i]);
			word = malloc((double_len) * sizeof(char*));
			if (word != NULL) {
				strcpy(word, lst[i]);
				doubled_list[double_idx++] = word;
			}
		}
	}
	free(lst);
	lst = doubled_list;
	curlist = double_idx;
	sizelist = double_idx;
}
	
	
		 

