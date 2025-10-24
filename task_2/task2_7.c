/* Вычисление значения выражения, содержащего цифры '0'-'9', знаки
* операций '+', '*' и скобки '(', ')''. ( Предполагается, что коды цифр
* упорядочены по возрастанию цифр и справедливо равенство '9'-'0'==9 как,
* например, в ASCII кодировке)
*/

#include <stdio.h>
#include <string.h>
#include <setjmp.h>

jmp_buf begin;

char curlex; /* текущая лексема */

void getlex(void); /* выделяет из входного потока очередную лексему */
int expr(void);    /* распознает выражение и вычисляет его значение */
int add(void);     /* распознает слагаемое и вычисляет его значение */
int power(void);   /* распознает возведение в степень и вычисляет его значение */
int mult(void);    /* распознает множитель и вычисляет его значение */
void error(void);  /* сообщает об ошибке в выражении и передает управление
                    в начало функции main (точка begin) */

typedef struct {
	int cnt;
	char op;
} operation;

void Sort(operation *mas, int n);

operation ops[5];

int main()
{
    int i;
	char *c;
	c = "+-*/^";
	int result; 
	for (i = 0; i <= 5; i++) {
		ops[i].cnt = 0;
		ops[i].op = c[i];
	}
    setjmp(begin);
    printf("==>");
    getlex();
    result = expr();
    if (curlex != '\n') error();
    printf("\n%d\n", result);
	Sort(ops, 5);
	printf("least popular operation is %c, it appears %d times\n", ops[0].op, ops[0].cnt);
	return 0;
}
void Sort(operation *mas, int n) {
	int i, j;
	operation t;
	
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (mas[j].cnt > mas[j+1].cnt) {
				t = mas[j];
				mas[j] = mas[j+1];
				mas[j+1] = t;
			}
}

void getlex()
{
    while ((curlex = getchar()) == ' ');
}

void error(void)
{
    printf("\nОШИБКА!\n");
    while (getchar() != '\n');
    longjmp(begin, 1);
}

int expr()
{
	int e = add(); 
	
    while ((curlex == '+') || (curlex == '-'))	
	{ 
		if (curlex == '-')
		{
			getlex();
			e -= add();
			ops[1].cnt += 1;
		}
	
		if (curlex == '+')
    	{	
        	getlex();
        	e += add();
			ops[0].cnt += 1;
    	}
	}
    return e;
}

int add()
{
    int b, a = power();
    while ((curlex == '/') || (curlex == '*'))
	{
		if (curlex == '/')
		{
			getlex();
			b = power();
			if (b == 0)
				error();
			else
				a /= b;
			ops[3].cnt += 1;
		}
		if (curlex == '*')
    	{
        	getlex();
       		a *= power();
			ops[2].cnt += 1;
		}
    }
    return a;
}

int power()
{
	int i, p = mult();
	while (curlex == '^')
	{
		getlex(); 
		int res = 1;
		int lim = power();
		for (i = 0; i < lim; i++)
			res *= p;
		p = res;
		ops[4].cnt += 1;
	}
	return p;
}

int mult()
{
    int m;
    switch (curlex)
    {
    case '0': case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
        m = curlex - '0';
        break;
    case '(':
        getlex();
        m = expr();
        if (curlex == ')') break;
        /* иначе ошибка - нет закрывающей скобки */
    default:
        error();
    }
    getlex();
    return m;
}

/* Сравните прототипы (в начале программы) и заголовки функций
* (в соответствующих определениях) error() и getlex() : информацию
* о параметрах (в данном случае пустые списки параметров - void) можно
* опускать в заголовке, если она есть в объявлении прототипа (как в случае
* с getlex) или не указывать в прототипе, а указать только в заголовке
* (как в случае с error). Тип обех функций - "функция, не возвращающая
* значения с пустым списком аргументов"
*/

