#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inf2post.h"




void PostfixNotation(const char *_infix, char *_postfix)	//methd of transforming edit field to postfix
{
	char stack[1000];	
	int st_ptr = 0;				// stack pointer
	int out_index = 0;		// input index
	int in_index = 0;		// output index

	//beginning of parsing the string
	do
	{
		char c = _infix[in_index];	// getting current letter

		switch (c)
		{
		case '+':
		case '-':
			_postfix[out_index++] = '|';//split symbol
			
			while (st_ptr != 0)
			{
				char op = stack[st_ptr - 1];	// operator on the top of stack
				if (op != '(')	// 
				{
					_postfix[out_index++] = op;	//put operator in output string
					st_ptr--;
					_postfix[out_index++] = '|';
					
				}
				else
					break;
			}
			// push operator
			push(stack, st_ptr, c);
			st_ptr++;
			break;

		case '*':
		case '/':
			// pop drmo stack operators with higher priority
			_postfix[out_index++] = '|';
			while (st_ptr != 0)
			{
				char op = stack[st_ptr - 1];
				if ((op == '^') || (op == '*') || (op == '/'))
				{
					_postfix[out_index++] = op;	
					st_ptr--;
					
					
				}
				else
					break;
			}
			push(stack, st_ptr, c);
			st_ptr++;
			break;

		case '(':
			_postfix[out_index++] = '|';
			push(stack, st_ptr, c);
			st_ptr++;
			break;

		case ')':
			// pop from stack elements without '('
			_postfix[out_index++] = '|';
			while (st_ptr != 0)
			{
				
				char op = pop(stack, st_ptr);	// getting operators
				st_ptr--;
				if (op == '(')					// if wi get ( then pop ends
					break;						 
				else
				{
					_postfix[out_index++] = op;	//put operator to the end of line
				}
			}
			break;

		case '^':
			_postfix[out_index++] = '|';
			push(stack, st_ptr, c);
			st_ptr++;
			break;
		case 's':	//sin
			
			push(stack, st_ptr, c);
			st_ptr++;
			break;
		case 'c':
			
			push(stack, st_ptr, c);
			st_ptr++;
			break;
		case 't':
			
			push(stack, st_ptr, c);
			st_ptr++;
			break;
		case 'k':		//ctg
			
			push(stack, st_ptr, c);
			st_ptr++;
			break;


		default:		// do if we got number or x
			_postfix[out_index] = c;
			out_index++;
			break;
		}

		in_index++;	
	} while (_infix[in_index] != 0);	

	// put all operators to the end of string
	while (st_ptr != 0)
	{
		_postfix[out_index++] = '|';
		_postfix[out_index++] = pop(stack, st_ptr);
		st_ptr--;
	}

	//null nymber
	_postfix[out_index] = 0;
	if (_postfix[0] == '|')
	{
		int i = 0;
		while (_postfix[i] != 0)
		{
			_postfix[i] = _postfix[i+1];
			i++;
		}

	}
	
}


void push(char *_stack, int _ptr, char data)
{
	_stack[_ptr++] = data;
}

char pop(char *_stack, int _ptr)
{
	return _stack[--_ptr];
}

void First_Transformation(char* _string,char* out_string)			//transforms sin(5),cos(6),tan(7),ctg(8)
{
	int i = 0;
	while (i<strlen(_string))
	{
		if (_string[i] == 's'&& _string[i + 1] == 'i'&&_string[i + 2] == 'n')
		{
			int j = 0;
			for ( j = 0; j < i; j++)
				out_string[j] = _string[j];
			out_string[j++] = 's';
			for (int k = j; k < strlen(_string) - 2; k++)
				out_string[k] = _string[k + 2];
			_string = out_string;
			i++;
		}
		if (_string[i] == 'c'&& _string[i + 1] == 'o'&&_string[i + 2] == 's')
		{
			int j = 0;
			for (j = 0; j < i; j++)
				out_string[j] = _string[j];
			out_string[j++] = 'c';
			for (int k = j; k < strlen(_string) - 2; k++)
				out_string[k] = _string[k + 2];
			_string = out_string;
			i++;
		}
		if (_string[i] == 't'&& _string[i + 1] == 'a'&&_string[i + 2] == 'n')
		{
			int j = 0;
			for (j = 0; j < i; j++)
				out_string[j] = _string[j];
			out_string[j++] = 't';
			for (int k = j; k < strlen(_string) - 2; k++)
				out_string[k] = _string[k + 2];
			_string = out_string;
			i++;
		}
		if (_string[i] == 'c'&& _string[i + 1] == 't'&&_string[i + 2] == 'g')
		{
			int j = 0;
			for (j = 0; j < i; j++)
				out_string[j] = _string[j];
			out_string[j++] = 'k';
			for (int k = j; k < strlen(_string) - 2; k++)
				out_string[k] = _string[k + 2];
			_string = out_string;
			i++;
		}
		else {
			out_string[i] = _string[i]; i++;
		}

	}
	
}
void Get_Double_Array(char _postfix[][100], double* real_numb_array)
{
	int z = 0;
	int j = 0;

	while (_postfix[0][z] != 0)
	{
		j = 0;
		if (_postfix[j][z] >= '0' && _postfix[j][z] <= '9')
		{
			j = 0;
			char c = _postfix[j][z];
			real_numb_array[z] = c - '0';
			j++;
			while (_postfix[j][z] >= '0'&&_postfix[j][z] <= '9')
			{
				c = _postfix[j][z];
				int x = real_numb_array[z];		//local variable
				real_numb_array[z] = 10 * x + (c - '0');
				j++;
			}
		}
		z++;
	}
}
void Get_Two_Dimensional_Char_Array(char* _poststring, char _postfix[][100])
{
	int j = 0;
	int z = 0;
	for (int i = 0; i < 100; i++)   //making massive[][] of chars from string a|+|x|5..
	{
		if (_poststring[i] == '|')
		{
			j++;
			z = 0;
		}
		else
		{
			if (z == 0)
			{
				_postfix[0][j] = _poststring[i];
				z = 1;
			}
			else
			{
				_postfix[z][j] = _poststring[i];
				z++;
			}
		}
	}
}