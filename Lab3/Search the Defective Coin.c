#include <stdio.h>
int weighings = 0;
int weigh(int coins[], int left, int right, int size)
{
    int sumLeft = 0;
    int sumRight = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        sumLeft += coins[left + i];
        sumRight += coins[right + i];
    }
    weighings++;
    if (sumLeft < sumRight)
        return -1;
    if (sumLeft > sumRight)
        return 1;
    return 0;
}
int findDefective(int coins[], int left, int n)
{
    int half;
    int result;
    if (n == 1)
        return -1;
    if (n == 2)
    {
        result = weigh(coins, left, left + 1, 1);
        if (result == -1)
            return left;
        if (result == 1)
            return left + 1;
        return -1;
    }
    half = n / 2;
    result = weigh(coins,left,left + half,half);
    if (result == -1)
        return findDefective(coins, left, half);
    if (result == 1)
        return findDefective(coins, left + half, half);
    if (n % 2 == 0)
        return -1;
    {
        int remaining = left + 2 * half;
        weighings++;
        if (coins[remaining] < coins[left])
            return remaining;
        return -1;
    }
}
int main()
{
    int n;
    int defective;
    int i;
    printf("Enter number of coins: ");
    scanf("%d", &n);
    int coins[n];
    printf("\nEnter the weight of each coin:\n");
    for (i = 0; i < n; i++)
    {
        printf("Coin %d: ", i + 1);
        scanf("%d", &coins[i]);
    }
    weighings = 0;
    defective = findDefective(coins, 0, n);
    if (defective == -1)
    {
        printf("No defective coin found.\n");
    }
    else
    {
        printf("Defective coin: Coin %d\n", defective + 1);
        printf("Weight: %d\n", coins[defective]);
    }
    printf("Number of weighings: %d\n", weighings);;
    return 0;
}
