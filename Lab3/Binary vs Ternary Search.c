#include <stdio.h>
#include <stdlib.h>
#define NUM_SIZES 9
long long binaryComparisons;
long long ternaryComparisons;
int binarySearch(int a[], int low, int high, int x)
{
    if (low > high)
        return -1;
    int mid = low + (high - low) / 2;
    binaryComparisons++;
    if (a[mid] == x)
        return mid;
    binaryComparisons++;
    if (x < a[mid])
        return binarySearch(a, low, mid - 1, x);
    return binarySearch(a, mid + 1, high, x);
}
int ternarySearch(int a[], int low, int high, int x)
{
    if (low > high)
        return -1;
    int third = (high - low) / 3;
    int mid1 = low + third;
    int mid2 = high - third;
    ternaryComparisons++;
    if (a[mid1] == x)
        return mid1;
    ternaryComparisons++;
    if (a[mid2] == x)
        return mid2;
    ternaryComparisons++;
    if (x < a[mid1])
    {
        return ternarySearch(
            a,
            low,
            mid1 - 1,
            x
        );
    }
    ternaryComparisons++;
    if (x > a[mid2])
    {
        return ternarySearch(
            a,
            mid2 + 1,
            high,
            x
        );
    }
    return ternarySearch(
        a,
        mid1 + 1,
        mid2 - 1,
        x
    );
}
int main()
{
    int sizes[NUM_SIZES] =
    {
        100,200,500,1000,2000,5000,10000,20000,50000
    };
    FILE *fp;
    fp = fopen("search_comparison.csv", "w");
    if (fp == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }
    fprintf(fp, "n,BinarySearch,TernarySearch\n");
    printf("\n");
    printf("============================================================\n");
    printf("       RECURSIVE BINARY SEARCH vs TERNARY SEARCH\n");
    printf("============================================================\n\n");
    printf("%10s %25s %25s\n",
           "n",
           "Binary Comparisons",
           "Ternary Comparisons");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < NUM_SIZES; i++)
    {
        int n = sizes[i];
        int *a = (int *)malloc(n * sizeof(int));
        if (a == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(fp);
            return 1;
        }
        for (int j = 0; j < n; j++)
            a[j] = j + 1;
        int x = n + 1;
        binaryComparisons = 0;
        ternaryComparisons = 0;
        binarySearch(a, 0, n - 1, x);
        ternarySearch(a, 0, n - 1, x);
       printf("%10d %25lld %25lld\n",n,binaryComparisons,ternaryComparisons);
        fprintf(fp,"%d,%lld,%lld\n",n,binaryComparisons,ternaryComparisons);
        free(a);
    }
    fclose(fp);
    printf("\n============================================================\n");
    printf("Conclusion:\n");
    printf("Binary Search uses fewer comparisons than\n");
    printf("Ternary Search for the tested input sizes.\n");
    printf("\nTherefore, Binary Search is experimentally better.\n");
    printf("============================================================\n");
    printf("\nCSV file generated: search_comparison.csv\n");
    return 0;
