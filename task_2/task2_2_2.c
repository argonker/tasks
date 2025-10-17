#include <stdio.h>
int main(){
	float x, a, result, deriative;
	printf("Введите последовательость\n");
	scanf("%f", &x);
	result = deriative = 0.0;
	while (scanf("%f", &a) != EOF){
		deriative *= x;
		deriative += result;
		result *= x;
		result += a;
	}
	printf("Значение многочлена = %.10g\n", result);
	printf("Значение производной = %.10g\n", deriative);
}
