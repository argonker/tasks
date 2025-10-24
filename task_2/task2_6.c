#include <stdio.h>
#include <stdlib.h>

typedef struct tnode {
	int elem;
	struct tnode *left;
	struct tnode *right;
} tnode;

void AddToTree(tnode **tree, int elem) {
	
	if (*tree == NULL) {
		*tree = (tnode*)malloc(sizeof(tnode));
		(*tree)->elem = elem;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
	}
	else {
		tnode *cur = *tree;
		if (cur->elem > elem) 
			AddToTree(&(cur->left), elem);
		else if (cur->elem < elem)
			AddToTree(&(cur->right), elem);
		else
			return;
	}
}

void DeleteFromTree(tnode **tree, int elem) {

	if (*tree == NULL) 
		return;
	
	tnode *cur = *tree;

	if (cur->elem > elem) 
		DeleteFromTree(&(cur->left), elem);
	else if (cur->elem < elem)
		DeleteFromTree(&(cur->right), elem);
	
	else {
		if ((cur->left == NULL) && (cur->right == NULL)) {
			free(cur);
			*tree = NULL;
		}
		else if (cur->left == NULL) {
			*tree = cur->right;
			free(cur);
		}
		else if (cur->right == NULL) {
			*tree = cur->left;
			free(cur);
		}

		else {
			tnode *min_node = cur->right;
			tnode *min_parent = cur;
			
			while (min_node->left != NULL) {
				min_parent = min_node;
				min_node = min_node->left;
			}
		
			cur->elem = min_node->elem;
			if (min_parent->left == min_node)
				min_parent->left = min_node->right;
			else
				min_parent->right = min_node->right;

			free(min_node);
		}
	}		
}

void SearchInTree(tnode *tree, int elem) {
	char *yes = "yes";
	char *no = "no";
	
	if (tree == NULL) {
		printf("%d %s\n", elem, no);
		return;
	}
	
	if (tree->elem > elem)
		SearchInTree(tree->left, elem);
	else if (tree->elem < elem)
		SearchInTree(tree->right, elem);
	else {
		printf("%d %s\n", elem, yes);
		return;
	}
}	

void FreeTree(tnode **tree) {
	
	if (*tree == NULL)
		return;
	
	FreeTree(&((*tree)->left));
	FreeTree(&((*tree)->right));
	free(*tree);
	*tree = NULL;
}

int main() {
	tnode *tree = NULL;
	char c;
	int elem;
	
	while (scanf(" %c%d", &c, &elem) == 2) {
		if (c == '+')
			AddToTree(&tree, elem);
		else if (c == '-')
			DeleteFromTree(&tree, elem);
		else
			SearchInTree(tree, elem);
	}			
	FreeTree(&tree);
}
