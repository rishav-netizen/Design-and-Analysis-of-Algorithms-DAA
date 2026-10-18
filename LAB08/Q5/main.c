#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Computes Maximum Sum Increasing Subsequence (MSIS) using Dynamic Programming
int solveMSIS(int arr[], int n, ll msis[], int parent[])
{
    if (n <= 0)
    {
        return -1;
    }

    for (int i = 0; i < n; i++)
    {
        msis[i] = (ll)arr[i];
        parent[i] = -1;
    }

    int max_idx = 0;
    ll max_sum = msis[0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i] && msis[j] + arr[i] > msis[i])
            {
                msis[i] = msis[j] + arr[i];
                parent[i] = j;
            }
        }
        if (msis[i] > max_sum)
        {
            max_sum = msis[i];
            max_idx = i;
        }
    }

    return max_idx;
}

// Reconstructs the MSIS sequence elements
int *reconstructMSIS(int arr[], int parent[], int max_idx, int *out_len)
{
    int len = 0;
    int curr = max_idx;
    while (curr != -1)
    {
        len++;
        curr = parent[curr];
    }
    *out_len = len;

    int *subseq = (int *)malloc(len * sizeof(int));
    if (!subseq)
    {
        return NULL;
    }

    curr = max_idx;
    for (int i = len - 1; i >= 0; i--)
    {
        subseq[i] = arr[curr];
        curr = parent[curr];
    }
    return subseq;
}

// Computes LIS length for comparison purposes
int computeLISLength(int arr[], int n)
{
    if (n <= 0)
    {
        return 0;
    }
    int *dp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
    }

    int max_lis = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i])
            {
                dp[j] = dp[j] + 1;
            }
        }
        if (dp[i] > max_lis)
        {
            max_lis = dp[i];
        }
    }
    free(dp);
    return max_lis;
}

// Displays MSIS DP state table
void printMSISTable(int arr[], int n, ll msis[], int parent[])
{
    printf("\n  Index i   : ");
    for (int i = 0; i < n; i++)
    {
        printf("%6d ", i);
    }
    printf("\n  Array A[i]: ");
    for (int i = 0; i < n; i++)
    {
        printf("%6d ", arr[i]);
    }
    printf("\n  msis[i]   : ");
    for (int i = 0; i < n; i++)
    {
        printf("%6lld ", msis[i]);
    }
    printf("\n  parent[i] : ");
    for (int i = 0; i < n; i++)
    {
        if (parent[i] == -1)
        {
            printf("     - ");
        }
        else
        {
            printf("%6d ", parent[i]);
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

    ll *msis = (ll *)malloc(n * sizeof(ll));
    int *parent = (int *)malloc(n * sizeof(int));

    int max_idx = solveMSIS(arr, n, msis, parent);
    ll max_sum = msis[max_idx];

    if (n <= 20)
    {
        printMSISTable(arr, n, msis, parent);
    }

    int seq_len = 0;
    int *subseq = reconstructMSIS(arr, parent, max_idx, &seq_len);

    printf("\n  ----------------- RESULT -----------------\n");
    printf("  Maximum Sum Increasing Subsequence : %lld\n", max_sum);
    printf("  Subsequence Elements (%d items)    : [ ", seq_len);
    for (int i = 0; i < seq_len; i++)
    {
        printf("%d%s", subseq[i], (i == seq_len - 1) ? " " : " + ");
    }
    printf(" ] = %lld\n", max_sum);
    printf("========================================================\n");

    free(msis);
    free(parent);
    free(subseq);
}

void runDemoCases()
{
    int demo1[] = {1, 101, 2, 3, 100, 4, 5};
    executeTestCase("Demo 1: Classic MSIS vs LIS Divergence", demo1, sizeof(demo1) / sizeof(demo1[0]));

    int demo2[] = {10, 5, 4, 3};
    executeTestCase("Demo 2: Strictly Decreasing Sequence", demo2, sizeof(demo2) / sizeof(demo2[0]));

    int demo3[] = {3, 4, 5, 10};
    executeTestCase("Demo 3: Strictly Increasing Sequence", demo3, sizeof(demo3) / sizeof(demo3[0]));

    int demo4[] = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    executeTestCase("Demo 4: Varied Numerical Scale", demo4, sizeof(demo4) / sizeof(demo4[0]));
}

int main()
{
    printf("========================================================\n");
    printf("   DAA LAB 8 - Q5: MAXIMUM SUM INCREASING SUBSEQUENCE   \n");
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
        printf("\nEnter number of positive integers in array: ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            printf("Invalid array size!\n");
            return 1;
        }

        int *arr = (int *)malloc(n * sizeof(int));
        printf("Enter %d positive integers:\n", n);
        for (int i = 0; i < n; i++)
        {
            if (scanf("%d", &arr[i]) != 1 || arr[i] <= 0)
            {
                printf("Error: elements must be positive integers! (Invalid at %d)\n", i);
                free(arr);
                return 1;
            }
        }

        executeTestCase("User Custom Problem Instance", arr, n);
        free(arr);
    }

    return 0;
}
