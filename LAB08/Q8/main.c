#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// Solves Optimal Binary Search Tree (CLRS Section 15.5)
void optimalBST(int n, const double p[], const double q[], double **e, double **w, int **root)
{
    // Base cases: subproblems with 0 keys (only dummy key d_{i-1})
    for (int i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // Subtree chain length l from 1 to n
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++)
            {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }
}

// Recursively prints parent-child relationships as defined in CLRS
void printTreeStructure(int i, int j, int **root, int parent, int is_left)
{
    if (i > j)
    {
        // Leaf dummy key
        if (parent == 0)
        {
            printf("  Dummy key d%d is the root of the tree.\n", j);
        }
        else if (is_left)
        {
            printf("  Dummy key d%d is the left child of key k%d\n", j, parent);
        }
        else
        {
            printf("  Dummy key d%d is the right child of key k%d\n", j, parent);
        }
        return;
    }

    int r = root[i][j];
    if (parent == 0)
    {
        printf("  Key k%d is the root of the tree\n", r);
    }
    else if (is_left)
    {
        printf("  Key k%d is the left child of key k%d\n", r, parent);
    }
    else
    {
        printf("  Key k%d is the right child of key k%d\n", r, parent);
    }

    printTreeStructure(i, r - 1, root, r, 1);
    printTreeStructure(r + 1, j, root, r, 0);
}

// Visual ASCII tree printer with indentation
void printAsciiTree(int i, int j, int **root, int depth, const char *prefix)
{
    if (i > j)
    {
        printf("%s|-- [d%d]\n", prefix, j);
        return;
    }

    int r = root[i][j];
    printf("%s|-- (k%d)\n", prefix, r);

    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s|   ", prefix);

    printAsciiTree(i, r - 1, root, depth + 1, new_prefix);
    printAsciiTree(r + 1, j, root, depth + 1, new_prefix);
}

// Displays DP tables: e, w, and root
void printOBSTTables(int n, double **e, double **w, int **root)
{
    printf("\n  Table e[i, j] (Expected Search Cost):\n");
    printf("     i \\ j | ");
    for (int j = 0; j <= n; j++)
    {
        printf("%7d ", j);
    }
    printf("\n  ---------+");
    for (int j = 0; j <= n; j++)
    {
        printf("--------");
    }
    printf("\n");
    for (int i = 1; i <= n + 1; i++)
    {
        printf("   %4d    | ", i);
        for (int j = 0; j <= n; j++)
        {
            if (j >= i - 1)
            {
                printf("%7.4f ", e[i][j]);
            }
            else
            {
                printf("%7s ", "-");
            }
        }
        printf("\n");
    }

    printf("\n  Table w[i, j] (Cumulative Probability Weight):\n");
    printf("     i \\ j | ");
    for (int j = 0; j <= n; j++)
    {
        printf("%7d ", j);
    }
    printf("\n  ---------+");
    for (int j = 0; j <= n; j++)
    {
        printf("--------");
    }
    printf("\n");
    for (int i = 1; i <= n + 1; i++)
    {
        printf("   %4d    | ", i);
        for (int j = 0; j <= n; j++)
        {
            if (j >= i - 1)
            {
                printf("%7.4f ", w[i][j]);
            }
            else
            {
                printf("%7s ", "-");
            }
        }
        printf("\n");
    }

    printf("\n  Table root[i, j] (Optimal Root Indices):\n");
    printf("     i \\ j | ");
    for (int j = 1; j <= n; j++)
    {
        printf("%5d ", j);
    }
    printf("\n  ---------+");
    for (int j = 1; j <= n; j++)
    {
        printf("------");
    }
    printf("\n");
    for (int i = 1; i <= n; i++)
    {
        printf("   %4d    | ", i);
        for (int j = 1; j <= n; j++)
        {
            if (j >= i)
            {
                printf("%5d ", root[i][j]);
            }
            else
            {
                printf("%5s ", "-");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void executeTestCase(const char *title, int n, const double p[], const double q[])
{
    printf("\n========================================================================\n");
    printf(" %s\n", title);
    printf("========================================================================\n");
    printf("  Number of Keys (n): %d\n", n);
    printf("  Key Probabilities p[1..%d]: { ", n);
    for (int i = 1; i <= n; i++)
    {
        printf("%.2f%s", p[i], (i == n) ? " " : ", ");
    }
    printf("}\n");
    printf("  Dummy Probabilities q[0..%d]: { ", n);
    for (int i = 0; i <= n; i++)
    {
        printf("%.2f%s", q[i], (i == n) ? " " : ", ");
    }
    printf("}\n");

    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));
    for (int i = 0; i <= n + 1; i++)
    {
        e[i] = (double *)malloc((n + 1) * sizeof(double));
        w[i] = (double *)malloc((n + 1) * sizeof(double));
        root[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    optimalBST(n, p, q, e, w, root);

    printOBSTTables(n, e, w, root);

    printf("  ----------------- OPTIMAL BST STRUCTURE -----------------\n");
    printf("  Minimum Expected Search Cost e[1, %d] = %.4f\n\n", n, e[1][n]);
    printf("  Subtree Relationships:\n");
    printTreeStructure(1, n, root, 0, 0);

    printf("\n  Hierarchical Visual Tree Layout:\n");
    printAsciiTree(1, n, root, 0, "  ");
    printf("========================================================================\n");

    for (int i = 0; i <= n + 1; i++)
    {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }
    free(e);
    free(w);
    free(root);
}

void runDemoCases()
{
    // Demo 1: Canonical CLRS Section 15.5 Example (n = 5)
    double p1[] = {0.00, 0.15, 0.10, 0.05, 0.10, 0.20};
    double q1[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    executeTestCase("Demo 1: Canonical CLRS 15.5 Benchmark (n = 5)", 5, p1, q1);

    // Demo 2: Simple 3-key instance
    double p2[] = {0.00, 0.45, 0.10, 0.05};
    double q2[] = {0.15, 0.10, 0.05, 0.10};
    executeTestCase("Demo 2: Skewed Search Probability Distribution (n = 3)", 3, p2, q2);
}

int main()
{
    printf("========================================================================\n");
    printf("      DAA LAB 8 - Q8: OPTIMAL BINARY SEARCH TREES (OBST)                \n");
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
        printf("\nEnter number of sorted keys n: ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Invalid number of keys!\n");
            return 1;
        }

        double *p = (double *)malloc((n + 1) * sizeof(double));
        double *q = (double *)malloc((n + 1) * sizeof(double));

        p[0] = 0.0;
        printf("Enter %d search probabilities p1 to pn for keys k1 to kn:\n", n);
        for (int i = 1; i <= n; i++)
        {
            printf("  p[%d]: ", i);
            if (scanf("%lf", &p[i]) != 1 || p[i] < 0.0)
            {
                printf("Invalid probability!\n");
                free(p);
                free(q);
                return 1;
            }
        }

        printf("Enter %d dummy probabilities q0 to qn for dummy keys d0 to dn:\n", n + 1);
        for (int i = 0; i <= n; i++)
        {
            printf("  q[%d]: ", i);
            if (scanf("%lf", &q[i]) != 1 || q[i] < 0.0)
            {
                printf("Invalid probability!\n");
                free(p);
                free(q);
                return 1;
            }
        }

        executeTestCase("User Custom Problem Instance", n, p, q);
        free(p);
        free(q);
    }

    return 0;
}
