#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 200

void copyArray(int dest[], int src[], int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

long long bubbleSortOptimized(int arr[], int n)
{
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped)
            break;
    }

    return comparisons;
}

long long bubbleSortNormal(int arr[], int n)
{
    long long comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main(void)
{
    srand((unsigned)time(NULL));

    FILE *fp = fopen("q3_data.csv", "w");

    if (fp == NULL)
    {
        printf("Error creating CSV file.\n");
        return 1;
    }

    fprintf(fp, "ArraySize,OptimizedComparisons,NormalComparisons\n");

    printf("%-10s %-22s %-22s\n", "Size", "Optimized", "Normal");
    printf("------------------------------------------------------------\n");

    for (int n = 10; n <= MAX_SIZE; n += 10)
    {
        int original[MAX_SIZE];
        int arr1[MAX_SIZE];
        int arr2[MAX_SIZE];

        for (int i = 0; i < n; i++)
            original[i] = rand() % 1000;

        copyArray(arr1, original, n);
        copyArray(arr2, original, n);

        long long optimized = bubbleSortOptimized(arr1, n);
        long long normal = bubbleSortNormal(arr2, n);

        printf("%-10d %-22lld %-22lld\n", n, optimized, normal);

        fprintf(fp,
                "%d,%lld,%lld\n",
                n,
                optimized,
                normal);
    }

    fclose(fp);

    printf("\nCSV file generated successfully: q3_data.csv\n");

    return 0;
}