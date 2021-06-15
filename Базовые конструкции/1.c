//1. Вывести квадратную матрицу по заданному N.
#include <stdio.h>

#define N 3


int main(){
    int matrix_line[N*N];
    int matrix_square[N][N];

    //Заполнение
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matrix_line[i*N+j] = (i*N+j) + 1;
            matrix_square[i][j] = (i*N+j) + 1;
        }
    }

    //Вывод
    printf("matrix_line:\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",matrix_line[i*N+j]);
        }
        printf("\n");
    }

    printf("\nmatrix_square\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",matrix_square[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}