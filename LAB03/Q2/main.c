#include <stdio.h>
#include <stdlib.h>

static long long totalWeight(const int coins[], int start, int count)
{
    long long total = 0;
    for (int i = 0; i < count; i++)
        total += coins[start + i];
    return total;
}

/* Returns the index of the lighter coin, or -1 when all coins are equal. */
static int findDefective(const int coins[], int low, int high, int normalIndex, int *weighings)
{
    int length = high - low + 1;

    if (length == 1)
    {
        if (normalIndex >= 0)
        {
            (*weighings)++;
            return coins[low] < coins[normalIndex] ? low : -1;
        }
        return -1;
    }

    int half = length / 2;
    int leftStart = low;
    int rightStart = low + half;
    long long leftWeight = totalWeight(coins, leftStart, half);
    long long rightWeight = totalWeight(coins, rightStart, half);
    (*weighings)++;

    if (leftWeight < rightWeight)
        return findDefective(coins, leftStart, rightStart - 1, rightStart, weighings);
    if (rightWeight < leftWeight)
        return findDefective(coins, rightStart, rightStart + half - 1, leftStart, weighings);

    /* With equal pans, a possible odd coin is the only remaining candidate. */
    if (length % 2 != 0)
    {
        int oddCoin = high;
        (*weighings)++;
        return coins[oddCoin] < coins[leftStart] ? oddCoin : -1;
    }

    return -1;
}

int main(void)
{
    int n;
    printf("Enter number of coins: ");
    if (scanf("%d", &n) != 1 || n < 2)
    {
        printf("Please enter at least 2 coins.\n");
        return 1;
    }

    int *coins = malloc((size_t)n * sizeof(*coins));
    if (coins == NULL)
        return 1;

    printf("Enter the %d coin weights: ", n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &coins[i]) != 1)
        {
            free(coins);
            return 1;
        }
    }

    int weighings = 0;
    int defective = findDefective(coins, 0, n - 1, -1, &weighings);
    if (defective == -1)
        printf("No lighter (defective) coin was found.\n");
    else
        printf("Lighter coin found at position %d (weight %d).\n", defective + 1, coins[defective]);
    printf("Balance comparisons used: %d\n", weighings);

    free(coins);
    return 0;
}
