// Method 2
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
int *mergeArrays(int **arr, int left, int right, int n, int *size)
{
    if (left == right)
    {
        int *temp = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
            temp[i] = arr[left][i];

        *size = n;
        return temp;
    }
    int mid = (left + right) / 2;
    int size1, size2;
    int *leftArr = mergeArrays(arr, left, mid, n, &size1);
    int *rightArr = mergeArrays(arr, mid + 1, right, n, &size2);
    int *merged = (int *)malloc((size1 + size2) * sizeof(int));
    merge(leftArr, size1, rightArr, size2, merged);
    free(leftArr);
    free(rightArr);
    *size = size1 + size2;
    return merged;
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
    int finalSize;
    int *result = mergeArrays(arr, 0, k - 1, n, &finalSize);
    printf("\nMerged Array:\n");
    for (int i = 0; i < finalSize; i++)
        printf("%d ", result[i]);
    printf("\n");
    free(result);
    for (int i = 0; i < k; i++)
        free(arr[i]);
    free(arr);
    return 0;
}