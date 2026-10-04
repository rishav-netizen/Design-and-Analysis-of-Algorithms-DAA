#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Solves the Rod Cutting problem using bottom-up dynamic programming
void solveRodCutting(int n, int price[], int r[], int s[])
{
    r[0] = 0;
    s[0] = 0;

    for (int j = 1; j <= n; j++)
    {
        int max_val = INT_MIN;
        int best_cut = -1;

        for (int i = 1; i <= j; i++)
        {
            int current_val = price[i] + r[j - i];
            if (current_val > max_val)
            {
                max_val = current_val;
                best_cut = i;
            }
        }

        r[j] = max_val;
        s[j] = best_cut;
    }
}

// Prints the optimal piece decomposition for a rod of length rod_len
void printDecomposition(int rod_len, int s[], int price[])
{
    int curr = rod_len;
    int first = 1;
    printf("[ ");
    while (curr > 0)
    {
        int cut_piece = s[curr];
        if (!first)
        {
            printf(" + ");
        }
        printf("%d\" ($%d)", cut_piece, price[cut_piece]);
        first = 0;
        curr -= cut_piece;
    }
    printf(" ]");
}

// Displays complete DP table and optimal cuts for all sub-lengths
void printRodCuttingTable(int n, int price[], int r[], int s[])
{
    printf("\n  Length (j) | Price p[j] | Max Revenue r[j] | First Cut s[j] | Optimal Pieces Decomposition\n");
    printf(" ------------+------------+------------------+----------------+--------------------------------\n");
    for (int j = 1; j <= n; j++)
    {
        printf("     %4d    |    $%4d   |       $%4d      |      %4d\"     | ", j, price[j], r[j], s[j]);
        printDecomposition(j, s, price);
        printf("\n");
    }
    printf("\n");
}

void executeTestCase(const char *title, int n, int price[])
{
    printf("\n========================================================================\n");
    printf(" %s\n", title);
    printf("========================================================================\n");
    printf("  Rod Total Length (n): %d inches\n", n);
    printf("  Market Price Table  : ");
    for (int i = 1; i <= n; i++)
    {
        printf("%d\"=$%d%s", i, price[i], (i == n) ? "" : ", ");
    }
    printf("\n");

    int *r = (int *)malloc((n + 1) * sizeof(int));
    int *s = (int *)malloc((n + 1) * sizeof(int));

    solveRodCutting(n, price, r, s);
    printRodCuttingTable(n, price, r, s);

    printf("  ----------------- RESULT FOR LENGTH n = %d -----------------\n", n);
    printf("  Maximum Revenue Obtainable : $%d\n", r[n]);
    printf("  Optimal Pieces Cut         : ");
    printDecomposition(n, s, price);
    printf("\n========================================================================\n");

    free(r);
    free(s);
}

void runDemoCases()
{
    // Demo 1: Canonical CLRS 10-inch price table
    int clrs_price[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    executeTestCase("Demo 1: Classic CLRS Textbook Pricing (n = 10)", 10, clrs_price);

    // Demo 2: Super-additive (No cuts made, leaving rod uncut is best)
    int super_additive[] = {0, 1, 6, 12, 22, 35};
    executeTestCase("Demo 2: Super-Additive Pricing (Optimal: Rod Uncut)", 5, super_additive);

    // Demo 3: Strictly sub-additive (Cutting all into 1-inch pieces is best)
    int sub_additive[] = {0, 4, 7, 10, 13, 16};
    executeTestCase("Demo 3: Sub-Additive Pricing (Optimal: All 1-inch cuts)", 5, sub_additive);
}

int main()
{
    printf("========================================================================\n");
    printf("      DAA LAB 8 - Q7: ROD CUTTING WITH RECONSTRUCTION                   \n");
    printf("========================================================================\n");
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
        int n;
        printf("\nEnter rod length n (in inches): ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Invalid rod length!\n");
            return 1;
        }

        int *price = (int *)malloc((n + 1) * sizeof(int));
        price[0] = 0;
        printf("Enter market price for piece lengths 1 to %d:\n", n);
        for (int i = 1; i <= n; i++)
        {
            printf("  Price for length %2d: ", i);
            if (scanf("%d", &price[i]) != 1 || price[i] < 0)
            {
                printf("Invalid price entered!\n");
                free(price);
                return 1;
            }
        }

        executeTestCase("User Custom Problem Instance", n, price);
        free(price);
    }

    return 0;
}
