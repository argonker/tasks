#include <stdio.h>
int main(){
	double eps, x, x_i, delta;
	printf("Введите число eps = ");
	scanf("%lf", &eps);
	while (scanf("%lf", &x) != EOF && x >= 0){
		for (x_i = 0.5*(1+x), (delta = x_i - 1); delta >= eps || delta <= -eps; x_i = 0.5*(x_i + x/x_i))
			delta = x_i - 0.5*(x_i + x/x_i);
		printf("sqrt(x) = %.10g\n", x_i);
	} 
}
