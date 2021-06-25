#include <stdio.h>


void print_bits_int(int digit){
    printf("%#X - ",digit);

    char count_bits = sizeof(int) * 8;
    char i;

    for(i = count_bits - 1; i >= 0 ; i--){
        unsigned char bit = (digit >> i) & 1;
        printf("%d",bit);
        if(0 == (i % 8)){
            printf(" ");
        }
    }
    
    printf("\n");
}

void print_bits(unsigned char digit){

    printf("%X - ",digit);
    char i;

    for(i = 7; i >= 0 ; i--){
        unsigned char bit = (digit >> i) & 0x1;
        printf("%d",bit);
    }
    
    printf("\n");
}

void print_bytes(int digit){
    char count_bytes = sizeof(int);
    char i;

    for(i = count_bytes - 1; i >= 0 ; i--){
        unsigned char b = (digit >> (i * 8)) & 0x000000FF;
        print_bits(b);
    }
}

unsigned char get_byte_int(int digit, unsigned char number_byte){
    //функция получения байта целого числа, с индексом number_byte
    unsigned char byte = (digit >> (number_byte * 8));
    
    return byte;
}

void replace_byte(int *digit ,unsigned char rep_byte, unsigned char number_byte){
    int byte_position = 0;
    int copy_digit = (*digit);

    byte_position = ~(0xFF << (number_byte * 8));    
    copy_digit = copy_digit & byte_position;

    int insert_byte = rep_byte;
    insert_byte = insert_byte  << (number_byte * 8);

    copy_digit = copy_digit | insert_byte;

    (*digit) = copy_digit;
}


//Замена байта с помощью указателя
void replace_byte_p(int *digit ,unsigned char rep_byte, unsigned char number_byte){
    char *pd = (char*)digit;
    if(number_byte < 3){
        pd += number_byte;
        *pd = rep_byte;
    }
}

int main(){
    int a = 0x00AABBCC;
    print_bits_int(a);
    replace_byte_p(&a,0xDD,1);

    print_bits_int(a);
    print_bytes(a);
}