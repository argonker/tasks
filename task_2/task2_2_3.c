#include <stdio.h>
int main(){
    float x, a, result, deriative, integral;
	int n;
    printf("Введите степень многочлена\n");
	scanf("%d", &n);
	printf("Введите последовательость\n");
    scanf("%f", &x);
    result = deriative = integral = 0.0;
    for (n = n + 1; scanf("%f", &a) != EOF; --n){
        deriative = deriative*x + result;
        result = result*x + a;
		integral = (integral + a/n)*x;
    }
    printf("Значение многочлена = %.10g\n", result);
    printf("Значение производной = %.10g\n", deriative);
	printf("Значение определенного интеграла = %.10g\n", integral);
}
