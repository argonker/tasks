#include <stdio.h>

double exponent(double x, char sign);
double power(double base, int x);
double str2double(char str[]);
int main() {
	char num[25];
	
	double power(double base, int n) {
		double p = 1;
		int i;
		for (i = 1; i <= n; ++i)
			p *= base;
		return p;	
	}
	
	double exponent(double x, char str[], int i) {
		int p = 0;
		double j = 10.0;
		if (str[i] == '-')
			j = 0.1;
		i += 1;
		while (str[i] != '\0') {
		 	p = p*10 + (str[i] - '0');
			i += 1;
		}
		return x * power(j, p);
	}
	
	double str2double(char str[]) {
		int p = 0, i = 0, sign = 1, is_exp = 0;
		double j, result = 0.0;
		if (num[i] == '-') {
			sign = -1;
			i += 1;
		}
		while (num[i] != '\0') {           
			if ((num[i] == 'e') || (num[i] == 'E'))
				is_exp = 1;
			if (num[i] == '.') {
				i += 1;
				for (j = 10.0; num[i] != '\0'; j*=10, i++) 
					if ((num[i] == 'e') || (num[i] == 'E')) {
						is_exp = 1;
						break;
					}	
					else
						result += (num[i] - '0')/j;
			}
			if (is_exp == 1) {
				i += 1;
				result = exponent(result, num, i);
			}
			else 
				result = result*10 + (num[i] - '0');
			i += 1;
		}
	return result * sign;
	}
	while ((scanf("%s", num)) != EOF)
		printf("%.10g\n", str2double(num));
}
