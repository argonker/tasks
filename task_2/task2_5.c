#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *link;
typedef char *elemtype;

typedef struct Node {
		char *elem;
		struct Node *next;
} node;

typedef link list;

void AppendToList(list *l, char *str) {
	node *tmp = (node*)malloc(sizeof(node));
	node *cur = *l;

	tmp->next = NULL;	
	tmp->elem = malloc(sizeof(char) * (strlen(str) + 1));
	
	strcpy(tmp->elem, str);

	if (*l == NULL) {
		*l = tmp;
		return;
	}
	while (cur->next != NULL)
		cur = cur->next;
	
	cur->next = tmp;
}

void PrintList(list l) {
	node *tmp;

	if (l == NULL) { 
		printf("[]\n");
		return;
	}

	tmp = l;
	printf("[");
	while (tmp != NULL) {
		printf("%s", tmp->elem);
		if (tmp->next != NULL)
			printf(", ");
		tmp = tmp->next;
	}
	printf("]\n");
}

void ExcludeFromList(list *l, char *str) {
	node *cur = *l;
	node *prev = NULL;
	
	if (*l == NULL)
		return;	

	while (cur->next != NULL) {	
		if (strcmp(cur->elem, str) == 0) {
			if (prev == NULL) {
				*l = cur->next;
				free(cur->elem);
				free(cur);
				cur = *l;
			}
			else {
				prev->next = cur->next;
				free(cur->elem);
				free(cur);
				cur = prev->next;
			}
		}	
		else {
			prev = cur;
			cur = cur->next;
		}
	}
}

void ReverseString(char *str) {
	char temp;
	int i, n = strlen(str) - 1;
	
	for (i = 0; i <= n/2; i++) {
		temp = str[i];
		str[i] = str[n-i];
		str[n-i] = temp;
	}
}


void ReverseList(list *l) {
	node *next = NULL;
	node *cur = *l;
	node *prev = NULL;

	while (cur != NULL) {	
		ReverseString(cur->elem);

		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*l = prev;
}	

void FreeList(list l) {
	if (l == NULL) 
		return;
	node *cur = l, *tmp;
	while (cur && cur->next) {
		tmp = cur;		
		cur = cur->next;
		free(tmp->elem);
		free(tmp);
	}
	free(cur->elem);
	free(cur);
}


int main() {
	list wordlist = NULL;
	int size = 16;
	char c, *buff = malloc(sizeof(*buff) * size);
	int i;
	while ((c = getchar()) != EOF) {
		i = 0;
		while ((c  != ' ') && (c != '\n')) {
			buff[i] = c;
			i++;
			if (i + 1 >= size) {
				size *= 2;
				buff = realloc(buff, sizeof(*buff) * size);
			}
			c = getchar();
		}
		if (i != 0) {
			buff[i++] = '\0';
			char str[i];
			strcpy(str, buff);
			AppendToList(&wordlist, str);
		}
	}
	ExcludeFromList(&wordlist, buff);
	PrintList(wordlist);
	ReverseList(&wordlist);
	PrintList(wordlist);
	FreeList(wordlist);
	free(buff);
}

		
		



