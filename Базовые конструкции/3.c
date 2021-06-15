//3. Заполнить верхний треугольник матрицы 1, а нижний 0. (размер матрицы нечетный)

/*
0 0 1
0 1 1
1 1 1
*/

#include <stdio.h>

#define N 3

int main(){

    if(0 == (N%2)){
        printf("even!");
        return 1;
    }

    int matrix_down[N][N] = {0};
    int matrix_top[N][N] = {0};
    int matrix_right[N][N] = {0};
    int matrix_left[N][N] = {0};

    //Нижний треугольник побочная диагональ
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i + 1; j++){
            matrix_down[i][(N-1)-j] = 1;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",matrix_down[i][j]);
        }   
        printf("\n");
    }

    printf("\n");
    //Верхний треугольник побочная диагональ
    for(int i = 0; i < N; i++){
        for(int j = 0; j < (N - i); j++){
            matrix_top[i][j] = 1;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",matrix_top[i][j]);
        }   
        printf("\n");
    }
    
    printf("\n");
    //Нижний треугольник главная диагональ
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= i; j++){
            matrix_left[i][j] = 1;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N ; j++){
            printf("%d ",matrix_left[i][j]);
        }   
        printf("\n");
    }

    printf("\n");
    //Верхний треугольник главная диагональ
    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
            matrix_right[i][j] = 1;
        }
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N ; j++){
            printf("%d ",matrix_right[i][j]);
        }   
        printf("\n");
    }

    printf("\n");
}

