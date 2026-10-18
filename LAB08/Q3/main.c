#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    DIR_NONE = 0,
    DIR_DIAG = 1, // Match (diagonal up-left '\')
    DIR_UP   = 2, // From above ('^')
    DIR_LEFT = 3  // From left ('<')
} Direction;

// Computes the LCS DP table and direction matrix
int computeLCS(const char *X, const char *Y, int m, int n, int **L, Direction **b)
{
    for (int i = 0; i <= m; i++)
    {
        L[i][0] = 0;
        b[i][0] = DIR_NONE;
    }
    for (int j = 0; j <= n; j++)
    {
        L[0][j] = 0;
        b[0][j] = DIR_NONE;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                L[i][j] = L[i - 1][j - 1] + 1;
                b[i][j] = DIR_DIAG;
            }
            else if (L[i - 1][j] >= L[i][j - 1])
            {
                L[i][j] = L[i - 1][j];
                b[i][j] = DIR_UP;
            }
            else
            {
                L[i][j] = L[i][j - 1];
                b[i][j] = DIR_LEFT;
            }
        }
    }

    return L[m][n];
}

// Reconstructs the actual LCS string from direction matrix
char *reconstructLCS(const char *X, int m, int n, Direction **b, int lcs_len)
{
    char *result = (char *)malloc((lcs_len + 1) * sizeof(char));
    if (!result)
    {
        return NULL;
    }
    result[lcs_len] = '\0';

    int i = m;
    int j = n;
    int idx = lcs_len - 1;

    while (i > 0 && j > 0)
    {
        if (b[i][j] == DIR_DIAG)
        {
            result[idx--] = X[i - 1];
            i--;
            j--;
        }
        else if (b[i][j] == DIR_UP)
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    return result;
}

// Prints the LCS DP and direction table
void printLCSTable(const char *X, const char *Y, int m, int n, int **L, Direction **b)
{
    printf("\n  LCS Tabulation Matrix L[i][j] (with traceback arrows):\n");
    printf("        j   0 ");
    for (int j = 1; j <= n; j++)
    {
        printf("%4c ", Y[j - 1]);
    }
    printf("\n    i       y ");
    for (int j = 1; j <= n; j++)
    {
        printf("%4d ", j);
    }
    printf("\n    ------------------");
    for (int j = 1; j <= n; j++)
    {
        printf("-----");
    }
    printf("\n");

    for (int i = 0; i <= m; i++)
    {
        if (i == 0)
        {
            printf("    0   x |   0 ");
        }
        else
        {
            printf("  %3d   %c | ", i, X[i - 1]);
        }

        for (int j = (i == 0 ? 1 : 0); j <= n; j++)
        {
            char dir_sym = ' ';
            if (b[i][j] == DIR_DIAG)
            {
                dir_sym = '\\';
            }
            else if (b[i][j] == DIR_UP)
            {
                dir_sym = '^';
            }
            else if (b[i][j] == DIR_LEFT)
            {
                dir_sym = '<';
            }

            printf("%c%2d ", dir_sym, L[i][j]);
        }
        printf("\n");
    }
    printf("    Legend: '\\' = Match (Diagonal), '^' = Up, '<' = Left\n\n");
}

void executeTestCase(const char *title, const char *X, const char *Y)
{
    int m = (int)strlen(X);
    int n = (int)strlen(Y);

    printf("\n========================================================\n");
    printf(" %s\n", title);
    printf("========================================================\n");
    printf("  Sequence X (len %d): \"%s\"\n", m, X);
    printf("  Sequence Y (len %d): \"%s\"\n", n, Y);

    int **L = (int **)malloc((m + 1) * sizeof(int *));
    Direction **b = (Direction **)malloc((m + 1) * sizeof(Direction *));
    for (int i = 0; i <= m; i++)
    {
        L[i] = (int *)malloc((n + 1) * sizeof(int));
        b[i] = (Direction *)malloc((n + 1) * sizeof(Direction));
    }

    int lcs_len = computeLCS(X, Y, m, n, L, b);

    if (m <= 15 && n <= 15)
    {
        printLCSTable(X, Y, m, n, L, b);
    }

    char *lcs_str = reconstructLCS(X, m, n, b, lcs_len);

    printf("  ----------------- RESULT -----------------\n");
    printf("  Longest Common Subsequence Length : %d\n", lcs_len);
    printf("  Reconstructed Subsequence String  : \"%s\"\n", lcs_str ? lcs_str : "");
    printf("========================================================\n");

    free(lcs_str);
    for (int i = 0; i <= m; i++)
    {
        free(L[i]);
        free(b[i]);
    }
    free(L);
    free(b);
}

void runDemoCases()
{
    executeTestCase("Demo 1: Canonical CLRS Textbook Instance", "ABCBDAB", "BDCABA");
    executeTestCase("Demo 2: DNA Bioinformatics Sequence Alignment", "AGGTAB", "GXTXAYB");
    executeTestCase("Demo 3: Completely Disjoint Sequences", "HELLO", "WORLD");
    executeTestCase("Demo 4: Identical Sequences", "DYNAMIC", "DYNAMIC");
}

int main()
{
    printf("========================================================\n");
    printf(" DAA LAB 8 - Q3: LONGEST COMMON SUBSEQUENCE (LCS)       \n");
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
        char seq1[1024];
        char seq2[1024];
        printf("\nEnter first sequence X: ");
        if (scanf("%1023s", seq1) != 1)
        {
            printf("Error reading sequence X!\n");
            return 1;
        }

        printf("Enter second sequence Y: ");
        if (scanf("%1023s", seq2) != 1)
        {
            printf("Error reading sequence Y!\n");
            return 1;
        }

        executeTestCase("User Custom Problem Instance", seq1, seq2);
    }

    return 0;
}
