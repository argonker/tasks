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

int AppendToList(list *l, char *str) {
	node *tmp = (node*)malloc(sizeof(node));
	node *cur = *l;

	tmp->next = NULL;	
	tmp->elem = malloc(sizeof(char) * (strlen(str) + 1));
	
	strcpy(tmp->elem, str);

	if ((l != NULL) && (*l == NULL)) {
		*l = tmp;
		return 0;
	}
	while (cur && (cur->next != NULL))
		cur = cur->next;
	
	cur->next = tmp;
}

int PrintList(list l) {
	node *tmp;
	int i;
	if (l == NULL) { 
		printf("[]\n");
		return 0;
	}
	tmp = l;
	printf("[ ");
	while (tmp != NULL) {
		printf("%s ", tmp->elem);
		tmp = tmp->next;
	}
	printf("]\n");
}

int ExcludeFromList(list *l, char *str) {
	node *q = *l;
	node *tmp = *l;
	
	if (*l == NULL)
		return 0;	
	
	if (strcmp(tmp->elem, str) == 0) {
		q = q->next;
		free(tmp->elem);
		free(tmp);
		*l = q;
	}
	while (q->next && (q->next->next != NULL)) {
		if (strcmp(q->next->elem, str) == 0) {
			tmp = q->next;
			q->next = q->next->next;
			free(tmp->elem);
			free(tmp);
		}	
		q = q->next;
	}
	return 0;
}	

int FreeList(list l) {
	if (!l) 
		return 1;
	node *cur = l, *tmp;
	while (cur && cur->next) {
		tmp = cur;		
		cur = cur->next;
		free(tmp->elem);
		free(tmp);
	}
	free(cur->elem);
	free(cur);
	return 0;
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
		buff[i++] = '\0';
		char str[i];
		strcpy(str, buff);
		AppendToList(&wordlist, str);
	}
	ExcludeFromList(&wordlist, buff);
	PrintList(wordlist);
	FreeList(wordlist);
	free(buff);
}

		
		



