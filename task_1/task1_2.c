#include <stdio.h>
int main() {
	int x,y;
	x = 0;
	y = 1;
	if ((x += 1) >= 0 || (y -= 5) >= 0)
		printf("%c", '\a');
	printf("%d\n", x);
	printf("%d\n", y);
	if ((x += 1) < 0 || (y -= 5) >= 0)
		printf("%c", '\a');
	printf("%d\n", x);
	printf("%d\n", y);
	if (false && (y -= 5))
		printf("%d", y);
}
