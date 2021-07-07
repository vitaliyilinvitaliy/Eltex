#include <string.h>

#include "keyboard.h"
#include "../operations/operation.h"


void logic(char *digit, char read_digit, enum Keys input_key){
    static int index_digit = 0;
    static char operand1[20] = "0\0", operand2[20] = "0\0", sign_operation = '^';
    static char flag_pmdm = 0, flag_answer = 0;
    
    if(strlen(digit) <= 17){
    
        if(read_digit >= '0' && read_digit <= '9'){
            
            if(flag_answer == 1){
                memset(digit,0,20);
                index_digit = 0;
                flag_answer = 0;
            }

            if(input_key != Keys0){
                digit[index_digit] = read_digit;
                index_digit++;
            }else{
                if(digit[index_digit] != '0'){
                    digit[index_digit] = read_digit;
                    index_digit++;
                }
            }
            
        }else{
            switch (input_key)
            {
            case KeysPlus:
                flag_pmdm = (flag_pmdm == 0)? 1 : 2;
                sign_operation = '+';
                break;
            case KeysMinus:
                flag_pmdm = (flag_pmdm == 0)? 1 : 2;
                sign_operation = '-';
                break;
            case KeysMult:
                flag_pmdm = (flag_pmdm == 0)? 1 : 2;
                sign_operation = '*';
                break;
            case KeysClear:
                if(flag_answer == 1){
                    memset(digit,0,20);
                    digit[0] = '0';
                    memset(operand1,0,20);
                    memset(operand2,0,20);
                }else{
                    if(index_digit > 1){
                        digit[index_digit - 1] = '\0';
                        index_digit--;
                    }else{
                        digit[0] = '0';
                        index_digit = 0;
                    }
                }
                
                break;
            case KeysDiv:
                flag_pmdm = (flag_pmdm == 0)? 1 : 2; 
                sign_operation = '/';
                break;
            case KeysEqual:
                if(flag_answer == 0){
                    strcpy(operand2,digit);
                    operationshandler(operand1,operand2,sign_operation,digit);
                    index_digit = strlen(digit);
                    memset(operand1,0,20);
                    memset(operand2,0,20);
                    sign_operation = '^';
                    flag_answer = 1;
                    flag_pmdm = 0;
                }
                
                break;
            default:

                break;
            }

            if(flag_pmdm == 2 && input_key != KeysDefault && input_key != KeysEqual){
                strcpy(operand2,digit);
                operationshandler(operand1,operand2,sign_operation,digit);
                sign_operation = '^';
                index_digit = strlen(digit);
                strcpy(operand1,digit);
                memset(operand2,0,20);
                flag_answer = 1;
                flag_pmdm = 2;
            }else{
                if(flag_pmdm == 1 && input_key != KeysDefault && input_key != KeysEqual){
                    strcpy(operand1,digit);
                    memset(digit,0,20);
                    index_digit = 0;
                    digit[0] = '0';
                    flag_answer = 0;
                }
            }
        }
    }else{
        if(input_key != KeysDefault){
            memset(operand1,0,20);
            memset(operand2,0,20);
            memset(digit,0,20);
            digit[0] = '0';
            digit[1] = '\0';
            index_digit = 0;
            flag_pmdm = 0;
            sign_operation = '^';
            flag_answer = 0;
        }
    }
}