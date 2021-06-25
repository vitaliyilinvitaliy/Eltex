#include <stdio.h>
#include <stdint.h>

int main(){
    uint16_t x = 0x0001;
    printf("%s-endian\n\n", *((uint8_t *) &x) ? "little" : "big");

    int a = 0xAABBCC;
    int *p_a = &a;
    int **pp_a = &p_a;

    printf("a = %#x\n",a);
    printf("p_a = %p\n",p_a);
    printf("*p_a = %#x\n",*p_a);
    printf("pp_a = %p\n",pp_a);
    printf("*pp_a = %p\n",*pp_a);
    printf("**pp_a = %#x\n\n",**pp_a);

    unsigned char *byte = (unsigned char*)&a;
    byte += 2; 
    *byte = 0xFF;
    printf("byte = %p\n",byte);
    printf("*byte = %#x\n",*byte);

    printf("new a = %#x\n",a);


}