#include <stdio.h>
#include <stdlib.h>

// Computes LIS using classical O(n^2) Dynamic Programming
int solveLIS_DP(int arr[], int n, int dp[], int parent[])
{
    if (n <= 0)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        parent[i] = -1;
    }

    int max_len = 1;
    int max_idx = 0;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > max_len)
        {
            max_len = dp[i];
            max_idx = i;
        }
    }

    return max_idx;
}

// Reconstructs LIS sequence from DP parent pointers
int *reconstructLIS(int arr[], int parent[], int max_idx, int max_len)
{
    int *subseq = (int *)malloc(max_len * sizeof(int));
    if (!subseq)
    {
        return NULL;
    }

    int curr = max_idx;
    for (int i = max_len - 1; i >= 0; i--)
    {
        subseq[i] = arr[curr];
        curr = parent[curr];
    }
    return subseq;
}

// Displays DP state table
void printLIS_DPTable(int arr[], int n, int dp[], int parent[])
{
    printf("\n  Index i   : ");
    for (int i = 0; i < n; i++)
    {
        printf("%4d ", i);
    }
    printf("\n  Array A[i]: ");
    for (int i = 0; i < n; i++)
    {
        printf("%4d ", arr[i]);
    }
    printf("\n  dp[i]     : ");
    for (int i = 0; i < n; i++)
    {
        printf("%4d ", dp[i]);
    }
    printf("\n  parent[i] : ");
    for (int i = 0; i < n; i++)
    {
        if (parent[i] == -1)
        {
            printf("   - ");
        }
        else
        {
            printf("%4d ", parent[i]);
        }
    }
    printf("\n");
}

void executeTestCase(const char *title, int arr[], int n)
{
    printf("\n========================================================\n");
    printf(" %s\n", title);
    printf("========================================================\n");
    printf("  Input Array A (n = %d): [ ", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d%s", arr[i], (i == n - 1) ? " " : ", ");
    }
    printf("]\n");

    int *dp = (int *)malloc(n * sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));

    int max_idx = solveLIS_DP(arr, n, dp, parent);
    int max_len = dp[max_idx];

    if (n <= 20)
    {
        printLIS_DPTable(arr, n, dp, parent);
    }

    int *subseq = reconstructLIS(arr, parent, max_idx, max_len);

    printf("\n  ----------------- RESULT -----------------\n");
    printf("  Length of LIS        : %d\n", max_len);
    printf("  Reconstructed LIS    : [ ");
    for (int i = 0; i < max_len; i++)
    {
        printf("%d%s", subseq[i], (i == max_len - 1) ? " " : ", ");
    }
    printf("]\n");
    printf("========================================================\n");

    free(dp);
    free(parent);
    free(subseq);
}

void runDemoCases()
{
    int demo1[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    executeTestCase("Demo 1: Classic Textbook Array", demo1, sizeof(demo1) / sizeof(demo1[0]));

    int demo2[] = {50, 40, 30, 20, 10};
    executeTestCase("Demo 2: Strictly Decreasing Sequence", demo2, sizeof(demo2) / sizeof(demo2[0]));

    int demo3[] = {1, 2, 3, 4, 5, 6, 7};
    executeTestCase("Demo 3: Strictly Increasing Sequence", demo3, sizeof(demo3) / sizeof(demo3[0]));

    int demo4[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    executeTestCase("Demo 4: Complex Permutation Array", demo4, sizeof(demo4) / sizeof(demo4[0]));
}

int main()
{
    printf("========================================================\n");
    printf("   DAA LAB 8 - Q4: LONGEST INCREASING SUBSEQUENCE       \n");
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
        int n;
        printf("\nEnter number of elements in array: ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Invalid array size!\n");
            return 1;
        }

        int *arr = (int *)malloc(n * sizeof(int));
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++)
        {
            if (scanf("%d", &arr[i]) != 1)
            {
                printf("Error reading element at index %d!\n", i);
                free(arr);
                return 1;
            }
        }

        executeTestCase("User Custom Problem Instance", arr, n);
        free(arr);
    }

    return 0;
}
