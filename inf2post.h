#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void push(char *_stack, int _ptr, char data);
char pop(char *_stack, int _ptr);
void Postfix_Notation(const char *_infix, char *_postfix);
void First_Transformation(char* _string, char* out_string);
void Get_Double_Array(char _postfix[][100], double* real_numb_array);
void Get_Two_Dimensional_Char_Array(char* _poststring, char _postfix[][100]);