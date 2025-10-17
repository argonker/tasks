#include <stdio.h>
int main(){
	float x, a, result;
	printf("Введите последовательость\n");
	scanf("%f", &x);
	result = 0.0;
	while (scanf("%f", &a) != EOF){
		result *= x;
		result += a;
	}
	printf("Значение многочлена = %.10g\n", result);
}
