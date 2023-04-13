#include <stdio.h>

#define SIZE 3

int trace(int matrix[SIZE][SIZE])
{
    int result = 0;
    for(int i = 0; i < SIZE; i++)
        result += matrix[i][i];
    return result;
}

void transpose(int matrix[SIZE][SIZE])
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = i + 1; j < SIZE; j++)
        {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

int isSingular (int matrix[][SIZE])
{
    int determinant = 0;
    for(int i = 0; i < SIZE; i++)
    {
        int i_1 = -1;
        int i_2 = -1;
        switch(i)
        {
            case 0: i_1 = 1; i_2 = 2; break;
            case 1: i_1 = 0; i_2 = 2; break;
            case 2: i_1 = 0; i_2 = 1; break;
        }
        if(i == 1) determinant -= matrix[0][i]*(matrix[1][i_1]*matrix[2][i_2] - matrix[2][i_1]*matrix[1][i_2]);
        else determinant += matrix[0][i]*(matrix[1][i_1]*matrix[2][i_2] - matrix[2][i_1]*matrix[1][i_2]);
    }
    // printf("Determinant: %d\n", determinant); // For debugging
    if(!determinant) return 1;
    else return 0;
}

void matrixMultiplication(int a[SIZE][SIZE], int b[SIZE][SIZE], int result[SIZE][SIZE])
{
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            for(int k = 0; k < SIZE; k++)
                result[i][j] += (a[i][k]*b[k][j]);
    printMatrix(result);
}

void printMatrix(int matrix[][SIZE])
{
    for(int i = 0; i < SIZE; i++)
    {
        for(int j = 0; j < SIZE; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    // Input A and B
    int a[SIZE][SIZE], b[SIZE][SIZE];
    printf("Enter matrix A:\n");
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            scanf("%d", &a[i][j]);
    printf("Enter matrix B:\n");
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            scanf("%d", &b[i][j]);
    // Trace
    printf("Trace A: %d\n", trace(a));
    printf("Trace B: %d\n", trace(b));
    // Transpose
    printf("Transpose A:\n");
    transpose(a);
    printMatrix(a);
    printf("Transpose B:\n");
    transpose(b);
    printMatrix(b);
    // Multiplication
    transpose(b); // Changing B back to itself from its transpose
    int result[SIZE][SIZE] = {0}; // Initializing the entire array to zero
    printf("A transpose multiplied by B:\n");
    matrixMultiplication(a, b, result);
    // Singularity
    if(isSingular(result)) printf("It is singular.\n");
    else printf("It is not singular.\n");
    return 0;
}