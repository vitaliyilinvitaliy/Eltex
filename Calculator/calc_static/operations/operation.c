#include "operation.h"
#include "../interface/gotoxy.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void operationshandler(const char *operand1,const char *operand2, char sign, char *result){
    long long int op1 = atoi(operand1);
    long long int op2 = atoi(operand2);
    long long int res = 0;

    
    switch (sign)
    {
    case '+':
        res = add_calc(op1,op2);
        sprintf(result,"%lld",res);
        break;
    case '-':
        res = minus_calc(op1,op2);
        sprintf(result,"%lld",res);
        break;
    case '/':
        if(op2 != 0){
            res = div_calc(op1,op2);
            sprintf(result,"%lld",res);
        }else{
            strcpy(result,"inf");
        }
        break;
    case '*':
        res = mult_calc(op1,op2);
        sprintf(result,"%lld",res);
        break;
    default:
        break;
    }
}