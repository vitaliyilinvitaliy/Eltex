//4. Заполнить матрицу числами от 1 до N^2 улиткой.
/*
1  2  3  4  5 
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
*/

#include <stdio.h>

#define N 7


int main(){
    if(N%2 != 1){
        return 1;
    }

    int matrix[N*N] = {0};

    int counter = 1;
    int len_line = N;
    int index = 0;

    while (counter <= (N*N))
    {
        for(int l = 0; l < len_line; l++, counter++, index++){
            matrix[index] = counter;
        }
        index += N-1;
        len_line = len_line - 1;
        
        for(int l = 0; l < len_line; l++, counter++, index += N){
            matrix[index] = counter;
        }
        index = index - (N+1);
        
        for(int l = 0; l < len_line; l++, counter++, index--){
            matrix[index] = counter;
        }
        index = index - (N-1);
        len_line = len_line - 1; 
        
        for(int l = 0; l < len_line; l++, counter++, index -= N){
            matrix[index] = counter;
        }
        index = index + (N+1);
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ",matrix[i*N+j]);
        }   
        printf("\n");
    }
}

/*
[0][0] = 1  [0][1] = 2  [0][2] = 3  [0][3] = 4  [0][4] = 5 
[1][0] = 16 [1][1] = 17 [1][2] = 18 [1][3] = 19 [1][4] = 6
[2][0] = 15 [2][1] = 24 [2][2] = 25 [2][3] = 20 [2][4] = 7
[3][0] = 14 [3][1] = 23 [3][2] = 22 [3][3] = 21 [3][4] = 8
[4][0] = 13 [4][1] = 12 [4][2] = 11 [4][3] = 10 [4][4] = 9

4 4 3 3 2 2 1 1

[0][0] = 1  [0][1] = 2  [0][2] = 3  [0][3] = 4  [0][4] = 5 
[1][0] = 6  [1][1] = 7  [1][2] = 8  [1][3] = 9  [1][4] = 10
[2][0] = 11 [2][1] = 12 [2][2] = 13 [2][3] = 14 [2][4] = 15
[3][0] = 16 [3][1] = 17 [3][2] = 18 [3][3] = 19 [3][4] = 20
[4][0] = 21 [4][1] = 22 [4][2] = 23 [4][3] = 24 [4][4] = 25

[0] = 1  [1] = 2  [2] = 3  [3] = 4  [4] = 5 
[5] = 16 [6] = 17 [7] = 18 [8] = 19 [9] = 6
[10] = 15 [11] = 24 [12] = 25 [13] = 20 [14] = 7
[15] = 14 [16] = 23 [17] = 22 [18] = 21 [19] = 8
[20] = 13 [21] = 12 [22] = 11 [23] = 10 [24] = 9
*/

/*
len
index
counter 
1 2 3 4 5 16 17 18 19 6 15 24 25 20 7 14 23 22 21 8 13 12 11 10 9
*/