#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

typedef unsigned long long ull;

// Computes the total number of distinct combinations to form target amount V
ull countCoinCombinations(int coins[], int n, int V, ull dp[])
{
    dp[0] = 1ULL;
    for (int v = 1; v <= V; v++)
    {
        dp[v] = 0ULL;
    }

    for (int i = 0; i < n; i++)
    {
        int coin = coins[i];
        for (int v = coin; v <= V; v++)
        {
            dp[v] += dp[v - coin];
        }
    }

    return dp[V];
}

// Computes full 2D DP table for display
void computeFull2DTable(int coins[], int n, int V, ull **table)
{
    for (int i = 0; i <= n; i++)
    {
        table[i][0] = 1ULL;
        for (int v = 1; v <= V; v++)
        {
            table[i][v] = 0ULL;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int coin = coins[i - 1];
        for (int v = 1; v <= V; v++)
        {
            table[i][v] = table[i - 1][v];
            if (v >= coin)
            {
                table[i][v] += table[i][v - coin];
            }
        }
    }
}

// Backtracking helper to print all distinct coin combinations
void printCombinationsDFS(int coins[], int n, int coin_idx, int rem, int buffer[], int buf_len, int *comb_count, int max_display)
{
    if (rem == 0)
    {
        (*comb_count)++;
        if (*comb_count <= max_display)
        {
            printf("    (%2d)  [ ", *comb_count);
            for (int i = 0; i < buf_len; i++)
            {
                printf("%d%s", buffer[i], (i == buf_len - 1) ? "" : " + ");
            }
            printf(" ]\n");
        }
        return;
    }

    for (int i = coin_idx; i < n; i++)
    {
        if (coins[i] <= rem)
        {
            buffer[buf_len] = coins[i];
            printCombinationsDFS(coins, n, i, rem - coins[i], buffer, buf_len + 1, comb_count, max_display);
        }
    }
}

void printTable2D(int coins[], int n, int V, ull **table)
{
    printf("\n  Full 2D DP Table [Coins Considered vs Target Amount]:\n");
    printf("  Coins \\ Amount | ");
    for (int v = 0; v <= V; v++)
    {
        printf("%4d ", v);
    }
    printf("\n  ---------------+");
    for (int v = 0; v <= V; v++)
    {
        printf("-----");
    }
    printf("\n");

    for (int i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            printf("  { }            | ");
        }
        else
        {
            printf("  <= coin %-6d | ", coins[i - 1]);
        }

        for (int v = 0; v <= V; v++)
        {
            printf("%4" PRIu64 " ", table[i][v]);
        }
        printf("\n");
    }
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

    ull *dp = (ull *)malloc((V + 1) * sizeof(ull));
    ull total_ways = countCoinCombinations(coins, n, V, dp);

    if (n <= 6 && V <= 20)
    {
        ull **table = (ull **)malloc((n + 1) * sizeof(ull *));
        for (int i = 0; i <= n; i++)
        {
            table[i] = (ull *)malloc((V + 1) * sizeof(ull));
        }

        computeFull2DTable(coins, n, V, table);
        printTable2D(coins, n, V, table);

        for (int i = 0; i <= n; i++)
        {
            free(table[i]);
        }
        free(table);
    }

    printf("\n  ----------------- RESULT -----------------\n");
    printf("  Total number of distinct combinations: %" PRIu64 "\n", total_ways);

    if (total_ways > 0 && V <= 40)
    {
        printf("\n  Listing combination breakdown (up to first 25):\n");
        int *buffer = (int *)malloc((V + 1) * sizeof(int));
        int comb_count = 0;
        int max_display = 25;
        printCombinationsDFS(coins, n, 0, V, buffer, 0, &comb_count, max_display);
        if (comb_count > max_display)
        {
            printf("    ... and %d more combinations (omitted for brevity).\n", comb_count - max_display);
        }
        free(buffer);
    }
    printf("========================================================\n");

    free(dp);
}

void runDemoCases()
{
    int demo1[] = {1, 2, 5};
    executeTestCase("Demo 1: Classic Textbook Example (C = {1, 2, 5}, V = 5)", demo1, 3, 5);

    int demo2[] = {2, 3, 5, 6};
    executeTestCase("Demo 2: Denominations Without Unit Coin (C = {2, 3, 5, 6}, V = 10)", demo2, 4, 10);

    int demo3[] = {2};
    executeTestCase("Demo 3: Impossible Odd Amount (C = {2}, V = 7)", demo3, 1, 7);

    int demo4[] = {1, 2, 3};
    executeTestCase("Demo 4: Small denominations (C = {1, 2, 3}, V = 15)", demo4, 3, 15);
}

int main()
{
    printf("========================================================\n");
    printf(" DAA LAB 8 - Q2: COIN CHANGE TOTAL NUMBER OF WAYS       \n");
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
