//method 1
#include <stdio.h>
#include <stdlib.h>
void merge(int a[], int sizeA, int b[], int sizeB, int result[])
{
    int i = 0, j = 0, k = 0;
    while (i < sizeA && j < sizeB)
    {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }
    while (i < sizeA)
        result[k++] = a[i++];
    while (j < sizeB)
        result[k++] = b[j++];
}
int main()
{
    int k, n;
    printf("Enter number of arrays: ");
    scanf("%d", &k);
    printf("Enter number of elements in each array: ");
    scanf("%d", &n);
    int **arr = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++)
    {
        arr[i] = (int *)malloc(n * sizeof(int));
        printf("Enter sorted elements of array %d:\n", i + 1);
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);
    }
    int currentSize = n;
    int *result = (int *)malloc(currentSize * sizeof(int));
    for (int i = 0; i < n; i++)
        result[i] = arr[0][i];
    for (int i = 1; i < k; i++)
    {
        int *temp = (int *)malloc((currentSize + n) * sizeof(int));
        merge(result, currentSize, arr[i], n, temp);
        free(result);
        result = temp;
        currentSize += n;
    }
    printf("\nMerged Array:\n");
    for (int i = 0; i < currentSize; i++)
        printf("%d ", result[i]);
    printf("\n");
    free(result);
    for (int i = 0; i < k; i++)
        free(arr[i]);
    free(arr);
    return 0;
}