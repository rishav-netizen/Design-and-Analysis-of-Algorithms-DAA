#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0;
int swaps = 0;

void Swap(int *a, int *b);
int Partition(int* arr, int low, int high);
void QuickSort(int* arr, int low, int high);
void GenerateRandomFile(char *filename, int n);
int* ReadArrayFromFile(char *filename, int *out_n);
void WriteArrayToFile(char *filename, int* arr, int n);
void DisplayLimit(int* arr, int n, int limit);

int main()
{
    srand(time(NULL));

    char *input_file = "unsorted.txt";
    char *output_file = "sorted.txt";

    int n;
    printf("Enter number of random elements (N): ");
    while (scanf("%d", &n) != 1 || n <= 0)
    { 
        printf("Invalid input! Try again: ");
        while (getchar() != '\n');
    }

    GenerateRandomFile(input_file, n);

    int read_n = 0;
    int *arr = ReadArrayFromFile(input_file, &read_n);
    
    if (arr == NULL)
    {
        printf("Error reading file!\n");
        return 1;
    }

    printf("Unsorted preview: ");
    DisplayLimit(arr, read_n, 15);

    clock_t start = clock();
    QuickSort(arr, 0, read_n - 1);
    clock_t end = clock();
    double time_taken = ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

    WriteArrayToFile(output_file, arr, read_n);

    printf("Sorted preview: ");
    DisplayLimit(arr, read_n, 15);

    printf("\nExecution Time: %.4f ms\n", time_taken);
    printf("Total Comparisons: %d\n", comparisons);
    printf("Total Swaps: %d\n", swaps);

    free(arr);
    return 0;
}

void Swap(int *a, int *b)
{
    if (a != b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
        swaps++;
    }
}

int Partition(int* arr, int low, int high)
{
    int mid = low + (high - low) / 2;
    Swap(&arr[mid], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        comparisons++;
        if (arr[j] <= pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void QuickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pivot_idx = Partition(arr, low, high);
        QuickSort(arr, low, pivot_idx - 1);
        QuickSort(arr, pivot_idx + 1, high);
    }
}

void GenerateRandomFile(char *filename, int n)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    int u, l;
    do
    {
        printf("Enter limits between which random numbers should be: ");
        scanf("%d %d", &l, &u);
        if (l > u)
        {
            printf("Invalid Input! Try again.\n");
        }
    } while (l > u);

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", rand() % (u - l + 1) + l);
    }
    fclose(fp);
}

int* ReadArrayFromFile(char *filename, int *out_n)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return NULL;

    fscanf(fp, "%d", out_n);
    int *arr = (int*)malloc((*out_n) * sizeof(int));

    for (int i = 0; i < *out_n; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }

    fclose(fp);
    return arr;
}

void WriteArrayToFile(char *filename, int* arr, int n)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);
}

void DisplayLimit(int* arr, int n, int limit)
{
    printf("{");
    int count = n > limit ? limit : n;
    for (int i = 0; i < count; i++)
    {
        printf("%d", arr[i]);
        if (i < count - 1)
            printf(", ");
    }
    if (n > limit)
        printf(", ...");
    printf("}\n");
}
