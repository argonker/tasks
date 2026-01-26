#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int i;
	int No_Newline = 0;
	int No_Separations = 0;
	
	for (i = 1; i < argc; i++) {
		if ((argv[i][0] == '-') && (strlen(argv[i]) == 2) && (i < 3)) {

			switch (argv[i][1]) {
			case 'n':
				No_Newline = 1;
				break;

			case 's':
				No_Separations = 1;
				break;
			}
		}
		else
			break;
	}

	for (i = (1 + No_Newline + No_Separations); i < argc; i++) 
		printf((No_Separations)?"%s":"%s ", argv[i]);
	
	if (!No_Newline)
		printf("\n");
}	
