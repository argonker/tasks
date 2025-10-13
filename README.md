# Task 2
## Task 2_1

**INTERFACE** \
eps -- *your input*

**PROGRAM** \
To calculate square root of `x` was used Newton's method\
To check the condition `|x_i - x_i+1| >= eps` was used double inequality:
```
delta >= eps || delta <= -eps
```
where ``delta = x_i - 0.5*(x_i + x/x_i)``
***

## Task 2_2_1

**INTERFACE**\
x -- point x \
sequence -- coefficients\ 
Spacebar, Tab, Enter -- separation\
Ctrl + D -- symbol of the end of file\

**PROGRAM**
To calculate the value of a polynomial at a point x was used Horner's scheme:
```
result *= x;
result += a;
```
***

## Task 2_2_2

This program is a modified version of **Task2_2_1**\
To calculate the value of a deriative at a point x was added new variable `deriative`\
Accumulation of the `deriative` happens before accumulation of the `result`:
```
deriative *= x;
deriative += result;
result *= x;
result += a;
```   
***

## Task 2_2_3

**INTERFACE**\
n -- degree of polynomial\
x -- point x\
sequence -- coefficients\
Spacebar, Tab, Enter -- separation\
Ctrl + D -- symbol of the end of file\

**PROGRAM**
This program is a modified version of **Task2_2_2**\
To calculate the value of the integral with integration limits from 0 to x was used Newton-Leibniz formula\
Accumulation of the `integral` happens afterwards accumulation of the `result` and `deriative`\

```
deriative = deriative*x + result;
result = result*x + a;
integral = (integral + a/n)*x;
```
***

## Task 2_3

**INTERFACE**\
i -- Fibonacci number ordinal\

**FUNCTIONS**

`int iterative(int i)` takes an `i` - Fibonacci number ordinal and prints `f_i` - Fibonacci number as a result\
This function iteratively accumulates the value in `f_i`\

`long fib(int i)` takes an `i` - Fibonacci number ordinal and returns `f_i` - Fibonacci as a result\
This function uses recursion and compute `f_i` with formula:\

`f_i = fib(i-1) + fib(i-2)`

**PROGRAM**\
To see the difference in speed of execution of functions it is enough to enter i=45 or bigger
***

## Task 2_4

**INTERFACE**\
real -- valid real number in C\
Spacebar, Tab, Enter -- separation\
real\
...\
Ctrl + D -- symbol of the end of the file to finish the program \

**FUNCTIONS**\

Function `double power(double base, int n)` implements raising to an integer power\

```
double power(double base, int n) {
	double p = 1;
    int i;
    for (i = 1; i <= n; ++i)
    	p *= base;
    return p;
    }
```
Function `double exponent(double x, char str[], int i) performs raising the integer \part to the power specified by the exponent using function `power()`:
`return x * power(j, p);`\
where j - base of the exponent\

Tracking of the sign of the exponent also occurs in this function:
```
double j = 10.0;
if (str[i] == '-')
	j = 0.1;
```
Function `double str2double(char str[])`

First of all this key function tracks a sign of the number and defines a variable `sign`:
```
int p = 0, i = 0, sign = 1, is_exp = 0;
double j, result = 0.0;
	if (num[i] == '-') {
    	sign = -1;
```
Then it iteratively accumulates the result:\
```
result = result*10 + (num[i] - '0');
```

and tracks the appearance of a point or exponent:
```
while (num[i] != '\0') {
	if ((num[i] == 'e') || (num[i] == 'E'))
    	is_exp = 1;
    if (num[i] == '.') {
   		i += 1; 
```
Appearence of a point starts a cycle:\
```
for (j = 10.0; num[i] != '\0'; j*=10, i++)
	if ((num[i] == 'e') || (num[i] == 'E')) {
    	is_exp = 1;
        break;
    }
    else
    	result += (num[i] - '0')/j;
```
that forms the final result\

Appearence of the exponent is tracked by variable `is_exp` and if `is_exp == 1`, function `exponent()` is executed to form the final result:
```
if (is_exp == 1) {
	i += 1;
  	result = exponent(result, num, i);
}
```
As a result function returns a production of a result and a sign that was saved earlier in the `sign` variable

**PROGRAM**
Program recieves a string `num`, then uses function `str2double()` to form an answer and prints it
*** 
