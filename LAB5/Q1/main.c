#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int *a, int *b);
int RandomizedPartition(int* arr, int low, int high);
int Partition(int* arr, int low, int high);
int QuickSelect(int* arr, int low, int high, int k);
void FindMedian(int* arr, int n, double *median, int *mid1, int *mid2);
void Display(int* arr, int n);
void RandomArray(int n, int *arr);

int main()
{
    srand(time(NULL));

    int n;
    printf("Enter number of elements: ");
    while (scanf("%d", &n) != 1 || n <= 0)
    { 
        printf("Invalid input! Try again: ");
        while (getchar() != '\n');
    }
    
    int* arr = (int*)malloc(n * sizeof(int));
    
    int choice;
    printf("Choose input method (1 for manual, 2 for random): ");
    while(scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid input!\nTry again: ");
        while(getchar() != '\n');
    }

    if (choice == 1)
    {
        for (int i = 0; i < n; i++)
        {
            printf("Element %d: ", i + 1);
            scanf("%d", &arr[i]);
        }
    }
    else if (choice == 2)
    {
        RandomArray(n, arr);
    }

    printf("Original Unsorted Array: ");
    Display(arr, n);

    double median;
    int mid1, mid2;

    FindMedian(arr, n, &median, &mid1, &mid2);

    printf("Array After Quickselect: ");
    Display(arr, n);

    if (n % 2 == 1)
    {
        printf("Median: %.2f (Value = %d)\n", median, mid1);
    }
    else
    {
        printf("Middle elements: %d and %d\n", mid1, mid2);
        printf("Median (Average): %.2f\n", median);
    }

    free(arr);
    return 0;
}

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

int RandomizedPartition(int* arr, int low, int high)
{
    int random_idx = low + rand() % (high - low + 1);
    Swap(&arr[random_idx], &arr[high]);
    return Partition(arr, low, high);
}

int QuickSelect(int* arr, int low, int high, int k)
{
    while (low <= high)
    {
        if (low == high)
        {
            return arr[low];
        }

        int pivot_idx = RandomizedPartition(arr, low, high);

        if (pivot_idx == k)
        {
            return arr[pivot_idx];
        }
        else if (pivot_idx > k)
        {
            high = pivot_idx - 1;
        }
        else
        {
            low = pivot_idx + 1;
        }
    }
    return arr[low];
}

void FindMedian(int* arr, int n, double *median, int *mid1, int *mid2)
{
    if (n % 2 == 1)
    {
        *mid1 = QuickSelect(arr, 0, n - 1, n / 2);
        *mid2 = *mid1;
        *median = (double)(*mid1);
    }
    else
    {
        *mid2 = QuickSelect(arr, 0, n - 1, n / 2);
        *mid1 = QuickSelect(arr, 0, (n / 2) - 1, (n / 2) - 1);
        *median = (*mid1 + *mid2) / 2.0;
    }
}

void Display(int* arr, int n)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("}\n");
}

void RandomArray(int n, int *arr)
{
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

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (u - l + 1) + l;
    }
}