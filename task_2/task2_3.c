#include <stdio.h>
int main(){
	int i;
	int iterative(int i){
		long f_i, f_0 = 0, f_1 = 1; 
		int j;
		if (i > 1){
			for (j = 0; j < i - 1 ; ++j){
				f_i = f_1 + f_0;
				f_0 = f_1;
				f_1 = f_i; 
				}
				printf("%ld\n", f_i);
			}
			else
				printf("%d\n", i);
	return 0;
	}	
	long fib(int i){
		long f_i;
		if (i > 1)
			f_i = fib(i-1) + fib(i-2);
		else if (i == 1)
			f_i = 1;
		else 
			f_i = 0;
	return f_i;
	}
	while (scanf("%d", &i) != EOF){
		printf("Итеративно: ");
		iterative(i);
		printf("Рекурсивно: %ld\n", fib(i));
	}
}
