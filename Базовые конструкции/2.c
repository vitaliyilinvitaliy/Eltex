//2. Вывести заданный массив размером N в обратном порядке.
#include <stdio.h>

#define N 10

int main(){
    int mass[N];

    printf("Input -> ");
    for(int i = 0; i < N; i++){
        mass[i] = i + 1;
        printf("%d ",mass[i]);
    }

    printf("\nOutput <-");
    for(int i = N - 1; i >= 0; i--){
        printf("%d ",mass[i]);
    }

    printf("\n");
}