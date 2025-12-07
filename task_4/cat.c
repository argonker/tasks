#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int n_flag = 0;
	int i = 1;
	int fd;
	char chr;
	int line_num = 1;
	int newline = 1;
	
	if ((argc > 1) && (argv[1][0] == '-') && (strlen(argv[1]) == 2)) 
		if (argv[1][1] == 'n') {
			 n_flag = 1;
			 i++;
		}
	
	for (; i < argc; i++) {
		if ((fd = open(argv[i], O_RDONLY)) == -1) {
			fprintf(stderr, "%s: cannot open '%s'\n", argv[0], argv[i]);
				return -1;
		}
    	while ((read(fd, &chr, 1)) > 0) {
        	if (n_flag && newline) {
            	printf("%6d  ", line_num);
                newline = 0;
            }
		    putchar(chr);  
            if (chr == '\n') {
            	newline = 1;
                line_num++;
            }
		}
            
        close(fd);
	}
	return 0;
}   
