#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int is_dir(const char *path) {
	struct stat path_stat;
	if (stat(path, &path_stat) == -1) 
		return 0;
	return S_ISDIR(path_stat.st_mode);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(stderr, "%s: missing file operand\n", argv[0]);
		return -1;
	}
	if (argc == 2) {
		fprintf(stderr, "%s: missing destination file operand after '%s'\n", argv[0], argv[1]);
		return -1;
	}
	if (!strcmp(argv[1], argv[2])) {
		fprintf(stderr, "%s: '%s' and '%s' are the same file\n", argv[0], argv[1], argv[2]);
		return -1;
	}

	char *destination = argv[argc-1];
	if (!is_dir(destination)) {
		if (argc > 3) {
			fprintf(stderr, "%s: target '%s': Not a directory\n", argv[0], destination);
			return -1;
		}
		if (access(argv[1], F_OK) == -1) {
            fprintf(stderr, "%s: cannot stat '%s': No such file of directory\n", argv[0], argv[1]);
			return -1;
		} else {
			rename(argv[1], destination);
			return 0;
		}
	} else {
		char fin_dest[1024];
		for (int i = 1; i < argc - 1; i++) {
			strcpy(fin_dest, destination);

			char *source = argv[i];
			struct stat source_stat;
			if (stat(source, &source_stat) == -1) 
            	fprintf(stderr, "%s: cannot stat '%s': No such file or directory\n", argv[0], source);

			char *source_base = strrchr(argv[i], '/');
			if (source_base)
				strcat(fin_dest, source_base);
			else {
				strcat(fin_dest, "/");
				strcat(fin_dest, source);
			}
			if (rename(source, fin_dest) == -1)
				fprintf(stderr, "%s: Error while moving '%s' in '%s'\n", argv[0], source, fin_dest);
		}
	}
	return 0;		
}				
