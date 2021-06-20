#include <stdio.h>

int func(int i){
    int k = 2 * i + 1024;
    return k;
}


int main(){
    int a = 0;

    for(int i = 0; i < 10; i++){
        a = func(i);
    }


}