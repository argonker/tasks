#include <stdio.h>
int main(){
	unsigned char y;
	float x;
	while (scanf("%f", &x) != EOF){
		y = (unsigned char)x;
		printf("%d\n", y);
	}
}
