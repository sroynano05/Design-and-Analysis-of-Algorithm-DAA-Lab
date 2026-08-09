#include <stdio.h>
void swap(double *a, double *b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}
int partition(double a[], int low, int high)
{
    double pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return i + 1;
}
void quickSort(double a[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}
void uniqueness(double a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] == a[i + 1])
        {
            printf("The array is not unique.\n");
            return;
        }
    }
    printf("The array is unique.\n");
}
int main()
{
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    double a[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &a[i]);
    }
    quickSort(a, 0, n - 1);
    uniqueness(a, n);
    return 0;
}
