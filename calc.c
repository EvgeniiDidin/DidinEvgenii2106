#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
int st_ptr = 0;		// указатель вершины стека
double Calc(double _x, char _postfix[][100], double* _real_numb_arr)
{
	double stack[10000];	// стек для хранения операндов


	double temp;
	int in_index = 0;

	double op_a, op_b;

	do
	{
		char c = _postfix[0][in_index];
		if ((c >= '0') && (c <= '9') || (c == 'x'))
		{
			if (c == 'x')
				temp = _x;
			else
			{
				temp = _real_numb_arr[in_index];
			}
		}
		else
		{
			if (c == 's' || c == 'c' || c == 't' || c == 'k')
			{
				op_a = pop_dou(stack);
				switch (c)
				{
				case 's':
					temp = sin(op_a);
					break;
				case 'c':
					temp = cos(op_a);
					break;
				case 't':
					temp = tan(op_a);
					break;
				case 'k':
					temp = 1/tan(op_a);
					break;
				}
			}
			else{
				op_b = pop_dou(stack);
				op_a = pop_dou(stack);

				switch (c)
				{
				case '+':
					temp = op_a + op_b;
					break;
				case '-':
					temp = op_a - op_b;
					break;
				case '*':
					temp = op_a * op_b;
					break;
				case '/':
					temp = op_a / op_b;
					break;
				case '^':
					temp = pow(op_a, op_b);
					break;
				}
			}
		}
		push_dou(stack, temp);
		in_index++;
	} while (_postfix[0][in_index] != -52);

	return pop_dou(stack);
}

void push_dou(double *_stack, double data)
{
	_stack[st_ptr++] = data;
}

double pop_dou(double *_stack)
{
	return _stack[--st_ptr];
}