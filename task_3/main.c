#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
 
int main() {
	
	while (v != Stop) {
		c = getsym();
		
		switch(v) {
			
			case Start:
				start();
				break;
		
			case Word:
				word();
				break;
			
			case Special:
				special();
				break;
			
			case Newline:
				newline();
				break;
		
			case Stop:
				break;
		}
	}

	if (curlist > 0) {
		termlist();
			
		printf("\n");
		printf("Initial list:\n");
		printlist();
		printf("\n");
		sortlist();
		printf("Sorted list:\n");
		printlist();
	}
	clearlist();
}
