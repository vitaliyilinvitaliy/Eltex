#ifndef _OPERATION_H_
#define _OPERATION_H_

long long int mult_calc(const long long int op1, const long long int op2);
long long int add_calc(const long long int op1, const long long int op2);
long long int minus_calc(const long long int op1, const long long int op2);
long long int div_calc(const long long int op1, const long long int op2);
void operationshandler(const char *operand1,const char *operand2, char sign, char *result);

#endif //_OPERATION_H_