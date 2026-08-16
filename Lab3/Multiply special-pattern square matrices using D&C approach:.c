#include <stdio.h>
void add(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}
void subtract(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}
void multiply(int n, int A[n][n], int B[n][n], int C[n][n])
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    int k = n / 2;
    int A1[k][k], A2[k][k];
    int B1[k][k], B2[k][k];
    int S1[k][k], S2[k][k];
    int S3[k][k], S4[k][k];
    int X[k][k], Y[k][k];
    int C1[k][k], C2[k][k];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];
            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }
    add(k, A1, A2, S1);
    add(k, B1, B2, S2);
    subtract(k, A1, A2, S3);
    subtract(k, B1, B2, S4);
    multiply(k, S1, S2, X);
    multiply(k, S3, S4, Y);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C1[i][j] = (X[i][j] + Y[i][j]) / 2;
            C2[i][j] = (X[i][j] - Y[i][j]) / 2;
        }
    }
   for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C1[i][j];
            C[i][j + k] = C2[i][j];
            C[i + k][j] = C2[i][j];
            C[i + k][j + k] = C1[i][j];
        }
    }
}
int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int A[n][n];
    int B[n][n];
    int C[n][n];
    printf("Enter first matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Enter second matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }
    multiply(n, A, B, C);
    printf("Result:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", C[i][j]);
        }

        printf("\n");
    }
    return 0;
}
