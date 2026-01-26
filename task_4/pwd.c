#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char *cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}
