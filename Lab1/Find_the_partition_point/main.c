#include <stdio.h>
int binarySearch(int arr[], int l, int r)
{
    if (l > r)
        return l;
    int mid = l + (r - l) / 2;
    if (arr[mid] == 1)
        return binarySearch(arr, l, mid - 1);
    else
        return binarySearch(arr, mid + 1, r);
}
int main()
{
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("Partition found at index: %d\n", binarySearch(arr, 0, n - 1));
    return 0;
}
