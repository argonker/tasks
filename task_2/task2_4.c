#include <stdio.h>

double exponent(double x, char sign);
double power(double base, int x);
double str2double(char str[]);
int main() {
	char num[25];
	double x;
	int cnt_dig, after_point, i;

	double power(double base, int n) {
		double p = 1;
		int i;
		for (i = 1; i <= n; ++i)
			p *= base;
		return p;	
	}
	
	double exponent(double x, char str[]) {
		int p = 0;
		double j = 10.0;
		if (str[i] == '-')
			j = 0.1;
		i += 1;
		while (str[i] != '\0') {
		 	p = p*10 + (str[i] - '0');
			i += 1;
		}
		if (p != after_point)
			if (j == 0.1) 
				cnt_dig = (p >= cnt_dig)? p+1+after_point: cnt_dig; 
			else
				cnt_dig += p - after_point;
		else
			cnt_dig = cnt_dig - after_point;
		return x * power(j, p);
	}
	
	double str2double(char str[]) {
		int p = 0, sign = 1, is_exp = 0, is_point = 0;
		double j, result = 0.0;
		i = 0;
		cnt_dig = 0;
		after_point = 0;
		if (num[i] == '-') {
			sign = -1;
			i += 1;
		}
		while ((num[i] != '\0') && (num[i] != '\n')) {           
			if ((num[i] == 'e') || (num[i] == 'E'))
				is_exp = 1;
			if (num[i] == '.') {
				i += 1;
				is_point = 1;
				for (j = 10.0; num[i] != '\0'; j*=10, i++) 
					if ((num[i] == 'e') || (num[i] == 'E')) {
						is_exp = 1;
						break;
					}	
					else {
						result += (num[i] - '0')/j;	
						cnt_dig += 1;
						after_point += 1;
					}
			}
			if (is_exp == 1) {
				i += 1;
				result = exponent(result, num);
			}
			else if (is_point == 0){
				result = result*10 + (num[i] - '0');
				cnt_dig += 1;
			}
			i += 1;
		}
	return result * sign;
	}
	while ((scanf("%s", num)) != EOF) 
		printf("%.10g, %d digits\n", str2double(num), cnt_dig);
}
