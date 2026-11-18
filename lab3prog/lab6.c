#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int DetMatrix(int n, int matrix[n][n]){
    int det = 0;
    if(n == 1){
        det = matrix[0][0];
        return det; 
    }
    else if(n==2){
        det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        return det;
    }   
    else{
        int minor[n-1][n-1];
        for(int k = 0; k<n; k++){
            int row = 0;
            int iskl = (k%2==0) ? matrix[0][k] : matrix[0][k] * -1;
            for(int i = 1; i < n; i++){
                int col = 0;
                for(int j = 0 ; j<n; j++){
                    if (j == k){
                        continue;
                    }
                    minor[row][col] = matrix[i][j];
                    col++;
                    }
                row++;
                }
                det += iskl * DetMatrix(n - 1, minor);
            }
        return det;
        }
}

int solution(int n, int Opredelitel_matrix, int matrix[n][n], int matrixB[n]){
    
    int RecoverMatrix[n][n];
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            RecoverMatrix[i][j] = matrix[i][j];
            }
        }
    printf("значения иксов:\n");
    for(int k = 0; k<n;k++){
        float solve = 0;
        for(int i = 0; i<n; i++){
            matrix[i][k] = matrixB[i];
            }
        solve = (float)DetMatrix(n, matrix) / (float)Opredelitel_matrix;
        printf("%4.4f\n",solve);
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                matrix[i][j] = RecoverMatrix[i][j];
                }
            }   
    }
    return 0;
}

int main(){
    int n = 3;
    srand(time(NULL));
    // printf("сколько матрица?\n");
    // scanf("%d", &n);
    printf("\n матрица:\n");
    int matrix[3][3] = {3,2,1,6,5,4,9,8,7};
    for(int i = 0; i<n ; i++) {
        for(int j = 0; j<n ; j++){
            // matrix[i][j] = -10 + (rand() % 21);
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    int Opredelitel_matrix = DetMatrix(n, matrix);
    printf("свободные члены :\n");
    int matrixB[3] = {1,-2,3};
    for(int i = 0; i<n ; i++) {   
        // matrixB[i] = -10 + (rand() % 21);
        printf("%4d", matrixB[i]);
        }
    
    printf("\n определитель = %d\n", Opredelitel_matrix);
    if (Opredelitel_matrix != 0){
        solution(n, Opredelitel_matrix, matrix, matrixB);
    }
    else{
        printf("нет единстенного решения\n");
    }
    return 0;
}