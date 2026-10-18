#include <stdio.h>
#include <stdlib.h>

void ClearInputBuffer();
void Display(int* arr, int n);
int Max(int a, int b);
int Knapsack(int n, int capacity, int* weights, int* profits);

int main()
{
    int n, capacity;
    
    while (1)
    {
        printf("Enter the number of items (> 0): ");
        if (scanf("%d", &n) == 1 && n > 0)
        {
            break;
        }
        printf("Invalid input. Please enter a positive integer.\n");
        ClearInputBuffer();
    }

    int* weights = (int*)malloc(n * sizeof(int));
    int* profits = (int*)malloc(n * sizeof(int));
    if (weights == NULL || profits == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(weights);
        free(profits);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        while (1)
        {
            printf("Enter weight and profit for item %d (space separated): ", i + 1);
            if (scanf("%d %d", &weights[i], &profits[i]) == 2 && weights[i] > 0 && profits[i] >= 0)
            {
                break;
            }
            printf("Invalid input. Please enter positive weight and non-negative profit.\n");
            ClearInputBuffer();
        }
    }

    while (1)
    {
        printf("Enter the knapsack capacity (> 0): ");
        if (scanf("%d", &capacity) == 1 && capacity > 0)
        {
            break;
        }
        printf("Invalid input. Please enter a positive integer.\n");
        ClearInputBuffer();
    }

    printf("Weights: ");
    Display(weights, n);
    
    printf("Profits: ");
    Display(profits, n);

    int max_profit = Knapsack(n, capacity, weights, profits);
    printf("Maximum profit is: %d\n", max_profit);

    free(weights);
    free(profits);

    return 0;
}

void ClearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void Display(int* arr, int n)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

int Max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

int Knapsack(int n, int capacity, int* weights, int* profits)
{
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++)
    {
        dp[i] = (int*)malloc((capacity + 1) * sizeof(int));
    }

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weights[i - 1] <= w)
            {
                dp[i][w] = Max(profits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][capacity];

    for (int i = 0; i <= n; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}

