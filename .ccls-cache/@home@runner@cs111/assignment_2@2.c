#include <stdio.h>
#include <stdlib.h>

void generateOriginalMatrix(int u, int m, int original_matrix[u][m])
{
    for(int i = 0; i < u; i++)
        for(int j = 0; j < m; j++)
            original_matrix[i][j] = (rand() % 5) + 1;
}

void removeRandomElements(int u, int m, int original_matrix[u][m],
                          int matrix_with_missing_elements[u][m])
{
    /*
        0 - Deletion
        1 - Retention
    */
    for(int i = 0; i < u; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int decision = rand()%2;
            if(decision) matrix_with_missing_elements[i][j] = original_matrix[i][j];
            else matrix_with_missing_elements[i][j] = 0;
        }        
    }
}

void fillMatrixRandomly(int u, int m, int matrix_with_missing_elements[u][m],
                        int matrix_filled_randomly[u][m])
{
    for(int i = 0; i < u; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(matrix_with_missing_elements[i][j]) 
                matrix_filled_randomly[i][j] = matrix_with_missing_elements[i][j];
            else 
                matrix_filled_randomly[i][j] = (rand()%5) + 1;
        }
    }
}

void fillMatrixWithRowAverage(int u, int m, int matrix_with_missing_elements[u][m],
                              int matrix_filled_with_row_average[u][m])
{
    for(int i = 0; i < u; i++)
    {
        
    }
}

void fillMatrixWithColumnAverage(int u, int m, int matrix_with_missing_elements[u][m],
                              int matrix_filled_with_column_average[u][m]);

void reportDeviation(int u, int m, int original[u][m], int matrix[u][m], int c)
{
    printf("\nThe deviation in case of Q(%c) is\n", c);
    for(int i = 0; i < u; i++)
    {
        for(int j = 0; j < m; j++)
            printf("%d ", (matrix[i][j] - original[i][j]));
        printf("\n");
    }
}

int main()
{
    int u = 0, m = 0;
    printf("Enter the number of users.\n");
    scanf("%d", &u);
    printf("Enter the number of movies.\n");
    scanf("%d", &m);
    int original_matrix[u][m];
    generateOriginalMatrix(u, m, original_matrix);
    int matrix_with_missing_elements[u][m];
    removeRandomElements(u, m, original_matrix, matrix_with_missing_elements);
    int matrix_filled_randomly[u][m];
    fillMatrixRandomly(u, m, matrix_with_missing_elements, matrix_filled_randomly);
    reportDeviation(u, m, original_matrix, matrix_filled_randomly, 'a');
    int matrix_filled_with_row_average[u][m];
    fillMatrixWithRowAverage(u, m, matrix_with_missing_elements, matrix_filled_with_row_average);
    reportDeviation(u, m, original_matrix, matrix_filled_with_row_average, 'b');
    int matrix_filled_with_column_average[u][m];
    fillMatrixWithColumnAverage(u, m, matrix_with_missing_elements, matrix_filled_with_column_average);
    reportDeviation(u, m, original_matrix, matrix_filled_with_column_average, 'c');
    return 0;
}