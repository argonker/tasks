#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
 
int main() {
	int end_of_line = 0;
	int end_of_read = 0;
	
	while (!end_of_read && v != Stop) {
		if (v != Special_1) {
			c = getsym();
			if (c == EOF)
				end_of_read = 1;
		}
		
		switch(v) {
			
			case Start:
				start();
				break;
		
			case Word:
				word();
				break;
			
			case Special_1:
				special();
				break;
			
			case Special_2:
				special2();
				break;
			
			case Newline:
				newline();
				break;
		
			case Stop:
				break;
	}	
		if ((c == '\n' || end_of_read) && curlist > 0 && !end_of_line) {
			termlist();
			
			printf("Initial list:\n");
			printlist();
			printf("\n");
			sortlist();
			printf("Sorted list:\n");
			printlist();
	
			clearlist();
			end_of_line = 1;
		} else if (c != '\n') 
			end_of_line = 0;
	}

	if (curlist > 0) {
		termlist();

		printf("Initial list:\n");
        printlist();
       	printf("\n");
       	sortlist();
       	printf("Sorted list:\n");
       	printlist();
    }
        clearlist();
}
