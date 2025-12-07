#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "%s: Usage <File1> <File2>\n", argv[0]);
        return -1;
	}

  	if (argv[1] == argv[2])
		return -1;

	int fd1, fd2;

	if ((fd1 = open(argv[1], O_RDONLY)) == -1) {
		fprintf(stderr, "%s: cannot open '%s'\n", argv[0], argv[1]);
		return -1;
	}
	if ((fd2 = open(argv[2], O_RDONLY)) == -1) {   
		fprintf(stderr, "%s: cannot open '%s'\n", argv[0], argv[1]);
		return -1;
	}
	
	int line = 1;
	int byte = 1;
	ssize_t a, b;
	char byte1, byte2;
	
	while (((a = read(fd1, &byte1, 1)) > 0) && ((b = read(fd2, &byte2, 1)) > 0)) {
		
		if (byte1 != byte2) {
			fprintf(stdout, "%s %s differ: byte %d, line %d\n",  argv[1], argv[2], byte, line);
			return 0;
		}
		if (byte1 == '\n') {
			line++;
			byte = 1;
		} else
			byte++;
	}
		
	if (a == 0) {
		if ((b = read(fd2, &byte2, 1)) > 0) {
			fprintf(stdout, "%s: EOF on '%s' after byte %d, line %d\n", argv[0], argv[1], byte, line);
			return 1;
		}
	} else if ((a > 0) && (b == 0)) {
		fprintf(stdout, "%s: EOF on '%s' after byte %d, line %d\n", argv[0], argv[2], byte, line);
		return 1;
	}
  	close(fd1);
	close(fd2);
    return 0;
}
