#include <stdio.h>

struct test1
{
    char a;
    int b;
};

union test1_un
{
    char a;
    int b;
};


int main(){
    struct test1 str_p;
    str_p.a = 1;
    str_p.b = 0xFFFFFFFF;

    size_t sstr = sizeof(struct test1);

    printf("sizeof = %lu\n", sstr);

    char *ptr = (char*)&str_p;
    struct test1 *ptrtest = &str_p;


    for(int i = 0; i < 8; i++){
        printf("%d ",*ptr);
        ptr += 1;
    }

    printf("\n");

    printf("union size = %lu\n",sizeof(union test1_un)); 

    union test1_un unts;
    unts.a = 0;
    unts.b = 12345;

    ptr = (char*)&unts;
    unts.a = 1;
    for(int i = 0; i < 4; i++){
        printf("%d ",*ptr);
        ptr += 1;
    }



}