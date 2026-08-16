#include <stdio.h>
#define MAX 64
int operations = 0;
void addMatrix(int A[MAX][MAX],
               int B[MAX][MAX],
               int C[MAX][MAX],
               int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
            operations++;
        }
    }
}
void multiply(int A[MAX][MAX],
              int B[MAX][MAX],
              int C[MAX][MAX],
              int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        operations++;
        return;
    }
    int k = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX];
    int A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX];
    int B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX];
    int C21[MAX][MAX], C22[MAX][MAX];
    int T1[MAX][MAX], T2[MAX][MAX];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }
    multiply(A11, B11, T1, k);
    multiply(A12, B21, T2, k);
    addMatrix(T1, T2, C11, k);
    multiply(A11, B12, T1, k);
    multiply(A12, B22, T2, k);
    addMatrix(T1, T2, C12, k);
    multiply(A21, B11, T1, k);
    multiply(A22, B21, T2, k);
    addMatrix(T1, T2, C21, k);
    multiply(A21, B12, T1, k);
    multiply(A22, B22, T2, k);
    addMatrix(T1, T2, C22, k);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];

            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}
void printMatrix(int A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }

        printf("\n");
    }
}
int main()
{
    int n;
    int A[MAX][MAX];
    int B[MAX][MAX];
    int C[MAX][MAX];
    printf("Enter size of matrix: ");
    scanf("%d", &n);
    printf("\nEnter Matrix A:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    printf("\nEnter Matrix B:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }
    operations = 0;
    multiply(A, B, C, n);
    printf("\n========================================\n");
    printf("Matrix A:\n");
    printMatrix(A, n);
    printf("\nMatrix B:\n");
    printMatrix(B, n);
    printf("\nResult Matrix C = A x B:\n");
    printMatrix(C, n);
    printf("\nNumber of operations = %d\n", operations);
    printf("========================================\n");
    return 0;
}
