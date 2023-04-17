#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateOriginalMatrix(int u, int m, int original[u][m]) {
  for (int i = 0; i < u; i++)
    for (int j = 0; j < m; j++)
      original[i][j] = (rand() % 5) + 1;
}

void removeRandomElements(int u, int m, int original[u][m],
                          int missing_elements[u][m]) {
  /*
      0 - Deletion
      1 - Retention
  */
  for (int i = 0; i < u; i++) {
    for (int j = 0; j < m; j++) {
      int decision = rand() % 2;
      if (decision)
        missing_elements[i][j] = original[i][j];
      else
        missing_elements[i][j] = 0;
    }
  }
}

void fillMatrixRandomly(int u, int m, int missing_elements[u][m],
                        int randomly_filled[u][m]) {
  for (int i = 0; i < u; i++) {
    for (int j = 0; j < m; j++) {
      if (missing_elements[i][j])
        randomly_filled[i][j] = missing_elements[i][j];
      else
        randomly_filled[i][j] = (rand() % 5) + 1;
    }
  }
}

void fillMatrixWithRowAverage(int u, int m, int missing_elements[u][m],
                              int rowavg[u][m]) {
  for (int i = 0; i < u; i++) {
    int n_nonzero = 0, row_avg = 0;
    double row_sum = 0;
    for (int j = 0; j < m; j++) {
      if (missing_elements[i][j]) {
        row_sum += missing_elements[i][j];
        rowavg[i][j] = missing_elements[i][j];
        n_nonzero++;
      }
    }
    if (n_nonzero)
      row_avg = round(row_sum / n_nonzero);
    else
      row_avg = rand() % 5 + 1; // To fix the n_nonzero = 0 case
    for (int j = 0; j < m; j++)
      if (!missing_elements[i][j])
        rowavg[i][j] = row_avg;
  }
}

void fillMatrixWithColumnAverage(int u, int m, int missing_elements[u][m],
                                 int columnavg[u][m]) {
  for (int i = 0; i < m; i++) {
    int n_nonzero = 0, column_avg = 0;
    double column_sum = 0;
    for (int j = 0; j < u; j++) {
      if (missing_elements[j][i]) {
        column_sum += missing_elements[j][i];
        columnavg[j][i] = missing_elements[j][i];
        n_nonzero++;
      }
    }
    if (n_nonzero)
      column_avg = round(column_sum / n_nonzero);
    else
      column_avg = rand() % 5 + 1; // To fix the n_nonzero = 0 case
    for (int j = 0; j < u; j++)
      if (!missing_elements[j][i])
        columnavg[j][i] = column_avg;
  }
}

void reportDeviation(int u, int m, int original[u][m], int matrix[u][m],
                     int c) {
  printf("\nThe deviation in case of Q(%c) is\n", c);
  for (int i = 0; i < u; i++) {
    for (int j = 0; j < m; j++)
      printf("%d ", (matrix[i][j] - original[i][j]));
    printf("\n");
  }
}

void fillMatrixWithRowColumnAverage(int u, int m, int missing_elements[u][m],
                                    int rowcolumnavg[u][m]) {
  int row_avg[u], column_avg[m];
  for (int i = 0; i < u; i++) {
    float row_sum = 0;
    int n_nonzero = 0;
    for (int j = 0; j < m; j++) {
      row_sum += missing_elements[i][j];
      if (missing_elements[i][j])
        n_nonzero++;
    }
    if (n_nonzero)
      row_avg[i] = round(row_sum / n_nonzero);
    else
      row_avg[i] = rand() % 5 + 1;
  }
  for (int i = 0; i < m; i++) {
    float column_sum = 0;
    int n_nonzero = 0;
    for (int j = 0; j < u; j++) {
      column_sum += missing_elements[j][i];
      if (missing_elements[j][i])
        n_nonzero++;
    }
    if (n_nonzero)
      column_avg[i] = round(column_sum / n_nonzero);
    else
      column_avg[i] = rand() % 5 + 1;
  }
  for (int i = 0; i < u; i++) {
    for (int j = 0; j < m; j++) {
      if (!missing_elements[i][j])
        rowcolumnavg[i][j] = round((row_avg[i] + column_avg[j]) / 2.0);
      else
        rowcolumnavg[i][j] = missing_elements[i][j];
    }
  }
}

int main() {
  srand(time(0));
  int u = 0, m = 0;
  printf("Enter the number of users.\n");
  scanf("%d", &u);
  printf("Enter the number of movies.\n");
  scanf("%d", &m);
  int original[u][m];
  generateOriginalMatrix(u, m, original);
  int missing_elements[u][m];
  removeRandomElements(u, m, original, missing_elements);
  int randomly_filled[u][m];
  fillMatrixRandomly(u, m, missing_elements, randomly_filled);
  reportDeviation(u, m, original, randomly_filled, 'a');
  int rowavg[u][m];
  fillMatrixWithRowAverage(u, m, missing_elements, rowavg);
  reportDeviation(u, m, original, rowavg, 'b');
  int columnavg[u][m];
  fillMatrixWithColumnAverage(u, m, missing_elements, columnavg);
  reportDeviation(u, m, original, columnavg, 'c');
  int rowcolumnavg[u][m];
  fillMatrixWithRowColumnAverage(u, m, missing_elements, rowcolumnavg);
  reportDeviation(u, m, original, rowcolumnavg, 'd');
  return 0;
}