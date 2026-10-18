#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Solves the Minimum Coin Change problem using Dynamic Programming
int solveMinCoins(int coins[], int n, int V, int dp[], int choice[])
{
    dp[0] = 0;
    choice[0] = 0;

    for (int i = 1; i <= V; i++)
    {
        dp[i] = INT_MAX;
        choice[i] = -1;
    }

    for (int i = 1; i <= V; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
            {
                if (dp[i - coins[j]] + 1 < dp[i])
                {
                    dp[i] = dp[i - coins[j]] + 1;
                    choice[i] = coins[j];
                }
            }
        }
    }

    if (dp[V] == INT_MAX)
    {
        return -1;
    }
    return dp[V];
}

// Reconstructs and prints the exact coins chosen
void printCoinReconstruction(int V, int choice[])
{
    if (V == 0)
    {
        printf("  Coins used: None (Amount is 0)\n");
        return;
    }
    if (choice[V] == -1)
    {
        printf("  Coins used: None (Target amount %d is unreachable)\n", V);
        return;
    }

    printf("  Optimal coins chosen: [ ");
    int curr = V;
    int first = 1;
    while (curr > 0)
    {
        int coin = choice[curr];
        if (!first)
        {
            printf("+ ");
        }
        printf("%d ", coin);
        first = 0;
        curr -= coin;
    }
    printf("] = %d\n", V);
}

// Prints DP state table for inspection
void printDPTable(int V, int dp[], int choice[])
{
    printf("\n  Amount v    : ");
    for (int i = 0; i <= V; i++)
    {
        printf("%4d ", i);
    }
    printf("\n  Min Coins   : ");
    for (int i = 0; i <= V; i++)
    {
        if (dp[i] == INT_MAX)
        {
            printf(" INF ");
        }
        else
        {
            printf("%4d ", dp[i]);
        }
    }
    printf("\n  Choice Coin : ");
    for (int i = 0; i <= V; i++)
    {
        if (choice[i] == -1)
        {
            printf("   - ");
        }
        else
        {
            printf("%4d ", choice[i]);
        }
    }
    printf("\n");
}

void executeTestCase(const char *title, int coins[], int n, int V)
{
    printf("\n========================================================\n");
    printf(" %s\n", title);
    printf("========================================================\n");
    printf("  Coin Denominations : { ");
    for (int i = 0; i < n; i++)
    {
        printf("%d%s", coins[i], (i == n - 1) ? " " : ", ");
    }
    printf("}\n");
    printf("  Target Amount (V)  : %d\n", V);

    int *dp = (int *)malloc((V + 1) * sizeof(int));
    int *choice = (int *)malloc((V + 1) * sizeof(int));

    int result = solveMinCoins(coins, n, V, dp, choice);

    if (V <= 25)
    {
        printDPTable(V, dp, choice);
    }

    printf("\n  ----------------- RESULT -----------------\n");
    if (result == -1)
    {
        printf("  Status: IMPOSSIBLE (-1)\n");
        printf("  Amount %d cannot be formed with the given coins.\n", V);
    }
    else
    {
        printf("  Minimum coins required: %d\n", result);
        printCoinReconstruction(V, choice);
    }
    printf("========================================================\n");

    free(dp);
    free(choice);
}

void runDemoCases()
{
    int demo1[] = {1, 5, 6, 9};
    executeTestCase("Demo 1: Canonical Non-Greedy Case", demo1, 4, 11);

    int demo2[] = {2, 5, 10, 20};
    executeTestCase("Demo 2: Standard Currency Breakdown", demo2, 4, 27);

    int demo3[] = {3, 5};
    executeTestCase("Demo 3: Impossible Amount (No combination sums to 7)", demo3, 2, 7);

    int demo4[] = {186, 419, 83, 408};
    executeTestCase("Demo 4: Larger Denominations", demo4, 4, 6249);
}

int main()
{
    printf("========================================================\n");
    printf("       DAA LAB 8 - Q1: MINIMUM COIN CHANGE PROBLEM       \n");
    printf("========================================================\n");
    printf("1. Run Automated Demonstration Cases\n");
    printf("2. Custom User Input\n");
    printf("Select option (1 or 2): ");

    int option = 1;
    if (scanf("%d", &option) != 1)
    {
        option = 1;
    }

    if (option == 1)
    {
        runDemoCases();
    }
    else
    {
        int n, V;
        printf("\nEnter number of coin denominations: ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Invalid number of denominations!\n");
            return 1;
        }

        int *coins = (int *)malloc(n * sizeof(int));
        printf("Enter %d distinct positive coin denominations:\n", n);
        for (int i = 0; i < n; i++)
        {
            if (scanf("%d", &coins[i]) != 1 || coins[i] <= 0)
            {
                printf("Invalid coin denomination at index %d!\n", i);
                free(coins);
                return 1;
            }
        }

        printf("Enter target amount (V >= 0): ");
        if (scanf("%d", &V) != 1 || V < 0)
        {
            printf("Invalid target amount!\n");
            free(coins);
            return 1;
        }

        executeTestCase("User Custom Problem Instance", coins, n, V);
        free(coins);
    }

    return 0;
}