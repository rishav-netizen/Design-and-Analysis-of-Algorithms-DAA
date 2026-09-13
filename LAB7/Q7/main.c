#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int m[MAX][MAX];
int s[MAX][MAX];

// Function prototypes
void MatrixChainOrder(int p[], int n);
void PrintOptimalParens(int i, int j);
void PrintTable(int n);

int main()
{
    int default_p[] = {30, 35, 15, 5, 10, 20, 25};
    int n = sizeof(default_p) / sizeof(default_p[0]) - 1;

    printf("--- Matrix Chain Multiplication (MCM) ---\n");
    printf("Using standard matrix dimensions: ");
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", default_p[i]);
    }
    printf("\n(Total matrices: %d)\n", n);

    MatrixChainOrder(default_p, n);
    PrintTable(n);

    printf("\nMinimum scalar multiplications: %d\n", m[1][n]);
    printf("Optimal parenthesization: ");
    PrintOptimalParens(1, n);
    printf("\n");

    printf("\nDo you want to test custom matrix dimensions? (1 for Yes, 0 for No): ");
    int choice;
    if (scanf("%d", &choice) == 1 && choice == 1)
    {
        int num_matrices;
        printf("Enter number of matrices: ");
        if (scanf("%d", &num_matrices) == 1 && num_matrices >= 1 && num_matrices < MAX)
        {
            int *p = malloc((num_matrices + 1) * sizeof(int));
            printf("Enter %d dimensions (p0 p1 ... pn): ", num_matrices + 1);
            for (int i = 0; i <= num_matrices; i++)
            {
                scanf("%d", &p[i]);
            }

            MatrixChainOrder(p, num_matrices);
            PrintTable(num_matrices);

            printf("\nMinimum scalar multiplications: %d\n", m[1][num_matrices]);
            printf("Optimal parenthesization: ");
            PrintOptimalParens(1, num_matrices);
            printf("\n");

            free(p);
        }
    }

    return 0;
}

void MatrixChainOrder(int p[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void PrintOptimalParens(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");
        PrintOptimalParens(i, s[i][j]);
        printf(" x ");
        PrintOptimalParens(s[i][j] + 1, j);
        printf(")");
    }
}

void PrintTable(int n)
{
    printf("\n--- M Table (Cost) ---\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i <= j)
                printf("%7d ", m[i][j]);
            else
                printf("%7s ", "-");
        }
        printf("\n");
    }

    printf("\n--- S Table (Split Points) ---\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i < j)
                printf("%3d ", s[i][j]);
            else
                printf("%3s ", "-");
        }
        printf("\n");
    }
}
