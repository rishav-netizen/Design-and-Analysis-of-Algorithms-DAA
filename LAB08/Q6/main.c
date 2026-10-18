#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    OP_MATCH,
    OP_SUBSTITUTE,
    OP_DELETE,
    OP_INSERT
} EditOp;

typedef struct
{
    EditOp op;
    char char_a;
    char char_b;
    int pos_a;
    int pos_b;
} TraceStep;

// Computes Edit Distance (Levenshtein Distance) matrix between string A and string B
int computeEditDistance(const char *A, const char *B, int m, int n, int **D)
{
    for (int i = 0; i <= m; i++)
    {
        D[i][0] = i;
    }
    for (int j = 0; j <= n; j++)
    {
        D[0][j] = j;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                D[i][j] = D[i - 1][j - 1]; // Match, cost 0
            }
            else
            {
                int del_cost = D[i - 1][j] + 1;     // Delete from A
                int ins_cost = D[i][j - 1] + 1;     // Insert into A
                int sub_cost = D[i - 1][j - 1] + 1; // Substitute

                int min_cost = del_cost;
                if (ins_cost < min_cost)
                {
                    min_cost = ins_cost;
                }
                if (sub_cost < min_cost)
                {
                    min_cost = sub_cost;
                }

                D[i][j] = min_cost;
            }
        }
    }

    return D[m][n];
}

// Reconstructs the traceback alignment and returns list of operations
TraceStep *reconstructTraceback(const char *A, const char *B, int m, int n, int **D, int *total_steps)
{
    int max_steps = m + n + 1;
    TraceStep *rev_steps = (TraceStep *)malloc(max_steps * sizeof(TraceStep));
    int count = 0;

    int i = m;
    int j = n;

    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1] && D[i][j] == D[i - 1][j - 1])
        {
            rev_steps[count++] = (TraceStep){OP_MATCH, A[i - 1], B[j - 1], i, j};
            i--;
            j--;
        }
        else if (i > 0 && j > 0 && D[i][j] == D[i - 1][j - 1] + 1)
        {
            rev_steps[count++] = (TraceStep){OP_SUBSTITUTE, A[i - 1], B[j - 1], i, j};
            i--;
            j--;
        }
        else if (i > 0 && D[i][j] == D[i - 1][j] + 1)
        {
            rev_steps[count++] = (TraceStep){OP_DELETE, A[i - 1], '-', i, j};
            i--;
        }
        else // j > 0 && D[i][j] == D[i][j - 1] + 1
        {
            rev_steps[count++] = (TraceStep){OP_INSERT, '-', B[j - 1], i, j};
            j--;
        }
    }

    *total_steps = count;
    TraceStep *steps = (TraceStep *)malloc(count * sizeof(TraceStep));
    for (int k = 0; k < count; k++)
    {
        steps[k] = rev_steps[count - 1 - k];
    }
    free(rev_steps);
    return steps;
}

// Displays the 2D DP Distance Table
void printDistanceTable(const char *A, const char *B, int m, int n, int **D)
{
    printf("\n  Edit Distance DP Table D[i][j]:\n");
    printf("        j   0 ");
    for (int j = 1; j <= n; j++)
    {
        printf("%4c ", B[j - 1]);
    }
    printf("\n    i       eps");
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
            printf("    0 eps | ");
        }
        else
        {
            printf("  %3d   %c | ", i, A[i - 1]);
        }

        for (int j = 0; j <= n; j++)
        {
            printf("%4d ", D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Displays detailed step-by-step transformation instructions and alignment
void printTracebackDetails(const TraceStep *steps, int total_steps)
{
    printf("  ----------------- TRACEBACK ALIGNMENT -----------------\n");
    printf("  Alignment Representation:\n  Source A: ");
    for (int k = 0; k < total_steps; k++)
    {
        if (steps[k].op == OP_INSERT)
        {
            printf(" _ ");
        }
        else
        {
            printf(" %c ", steps[k].char_a);
        }
    }
    printf("\n            ");
    for (int k = 0; k < total_steps; k++)
    {
        if (steps[k].op == OP_MATCH)
        {
            printf(" | ");
        }
        else if (steps[k].op == OP_SUBSTITUTE)
        {
            printf(" S ");
        }
        else if (steps[k].op == OP_DELETE)
        {
            printf(" D ");
        }
        else
        {
            printf(" I ");
        }
    }
    printf("\n  Target B: ");
    for (int k = 0; k < total_steps; k++)
    {
        if (steps[k].op == OP_DELETE)
        {
            printf(" _ ");
        }
        else
        {
            printf(" %c ", steps[k].char_b);
        }
    }
    printf("\n\n  Step-by-Step Transformation Operations:\n");

    int op_idx = 1;
    for (int k = 0; k < total_steps; k++)
    {
        switch (steps[k].op)
        {
            case OP_MATCH:
            {
                printf("    [Step %2d] MATCH      : '%c' == '%c' (Cost: 0)\n", op_idx++, steps[k].char_a, steps[k].char_b);
                break;
            }
            case OP_SUBSTITUTE:
            {
                printf("    [Step %2d] SUBSTITUTE : Replace '%c' with '%c' (Cost: 1)\n", op_idx++, steps[k].char_a, steps[k].char_b);
                break;
            }
            case OP_DELETE:
            {
                printf("    [Step %2d] DELETE     : Remove '%c' from source string (Cost: 1)\n", op_idx++, steps[k].char_a);
                break;
            }
            case OP_INSERT:
            {
                printf("    [Step %2d] INSERT     : Insert '%c' into source string (Cost: 1)\n", op_idx++, steps[k].char_b);
                break;
            }
        }
    }
}

void executeTestCase(const char *title, const char *A, const char *B)
{
    int m = (int)strlen(A);
    int n = (int)strlen(B);

    printf("\n========================================================\n");
    printf(" %s\n", title);
    printf("========================================================\n");
    printf("  Source String A (len %d): \"%s\"\n", m, A);
    printf("  Target String B (len %d): \"%s\"\n", n, B);

    int **D = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
    {
        D[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    int distance = computeEditDistance(A, B, m, n, D);

    if (m <= 15 && n <= 15)
    {
        printDistanceTable(A, B, m, n, D);
    }

    int total_steps = 0;
    TraceStep *steps = reconstructTraceback(A, B, m, n, D, &total_steps);

    printf("  ----------------- RESULT -----------------\n");
    printf("  Minimum Edit Distance (Levenshtein): %d\n\n", distance);

    printTracebackDetails(steps, total_steps);
    printf("========================================================\n");

    for (int i = 0; i <= m; i++)
    {
        free(D[i]);
    }
    free(D);
    free(steps);
}

void runDemoCases()
{
    executeTestCase("Demo 1: Classic NLP Example", "kitten", "sitting");
    executeTestCase("Demo 2: Calendar Words Transformation", "sunday", "saturday");
    executeTestCase("Demo 3: High Edit Variance", "intention", "execution");
    executeTestCase("Demo 4: Identical Strings", "algorithm", "algorithm");
}

int main()
{
    printf("========================================================\n");
    printf(" DAA LAB 8 - Q6: EDIT DISTANCE WITH TRACEBACK INFO      \n");
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
        char strA[1024];
        char strB[1024];
        printf("\nEnter source string A: ");
        if (scanf("%1023s", strA) != 1)
        {
            printf("Error reading string A!\n");
            return 1;
        }

        printf("Enter target string B: ");
        if (scanf("%1023s", strB) != 1)
        {
            printf("Error reading string B!\n");
            return 1;
        }

        executeTestCase("User Custom Problem Instance", strA, strB);
    }

    return 0;
}
