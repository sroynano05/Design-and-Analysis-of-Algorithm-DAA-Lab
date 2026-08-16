#include <stdio.h>
int comparisons = 0;
typedef struct
{
    int min;
    int max;
} Result;
Result findMinMax(int a[], int low, int high)
{
    Result result;
    Result left;
    Result right;
    if (low == high)
    {
        result.min = a[low];
        result.max = a[low];
        return result;}
    if (high == low + 1)
    {
        comparisons++;
        if (a[low] < a[high])
        {
            result.min = a[low];
            result.max = a[high];
        }
        else
        {
            result.min = a[high];
            result.max = a[low];
        }
        return result;
    }
    int mid = low + (high - low) / 2;
    left = findMinMax(a, low, mid);
    right = findMinMax(a, mid + 1, high);
    comparisons++;
    if (left.min < right.min)
        result.min = left.min;
    else
        result.min = right.min;
    comparisons++;
    if (left.max > right.max)
        result.max = left.max;
    else
        result.max = right.max;
    return result;
}
int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    comparisons = 0;
    Result result = findMinMax(a, 0, n - 1);
    printf("\n========================================\n");
    printf("Minimum = %d\n", result.min);
    printf("Maximum = %d\n", result.max);
    printf("Number of comparisons = %d\n", comparisons);
    if (n % 2 == 0)
    {
        int bound = (3 * n) / 2 - 2;
        printf("Theoretical bound = %d\n", bound);
        if (comparisons <= bound)
            printf("Bound validated: YES\n");
        else
            printf("Bound validated: NO\n");
    }
    else
    {
        int bound = (3 * (n - 1)) / 2;
        printf("Theoretical bound = %d\n", bound);
        if (comparisons <= bound)
            printf("Bound validated: YES\n");
        else
            printf("Bound validated: NO\n");
    }
    printf("========================================\n");
    return 0;
}
