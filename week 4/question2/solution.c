#include <stdio.h>
void merge(int a[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = 0;
    int temp[high - low + 1];
    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= high)
        temp[k++] = a[j++];
    for (i = low, k = 0; i <= high; i++, k++)
        a[i] = temp[k];
}
void mergeSort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}
int binarySearch(int a[], int n, int key)
{
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (a[mid] == key)
            return 1;

        if (a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return 0;
}
int pairSum(int S1[], int S2[], int n, int x)
{
    mergeSort(S2, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        int required = x - S1[i];
        if (binarySearch(S2, n, required))
            return 1;
    }
    return 0;
}
int main()
{
    int n, x;
    printf("Enter size of sets: ");
    scanf("%d", &n);
    int S1[n], S2[n];
    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S1[i]);
    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &S2[i]);
    printf("Enter x: ");
    scanf("%d", &x);
    if (pairSum(S1, S2, n, x))
        printf("Pair exists\n");
    else
        printf("Pair does not exist\n");
    return 0;
}