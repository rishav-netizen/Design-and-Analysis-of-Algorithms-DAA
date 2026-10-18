#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int *a, int *b);
int Partition(int* arr, int low, int high);
int RandomizedPartition(int* arr, int low, int high);
int QuickSelect(int* arr, int low, int high, int k);
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

    int k;
    printf("Enter K (1 <= K <= %d): ", n);
    while (scanf("%d", &k) != 1 || k < 1 || k > n)
    {
        printf("\tInvalid input, try again!\n");
        printf("Enter K: ");
        while (getchar() != '\n');
    }

    printf("Original Unsorted Array: ");
    Display(arr, n);

    int kth_smallest = QuickSelect(arr, 0, n - 1, k - 1);

    printf("Array After Quickselect: ");
    Display(arr, n);

    printf("Result: %dth smallest element is %d\n", k, kth_smallest);

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

int QuickSelect(int* arr, int low, int high, int target_idx)
{
    while (low <= high)
    {
        if (low == high)
        {
            return arr[low];
        }

        int pivot_idx = RandomizedPartition(arr, low, high);

        if (pivot_idx == target_idx)
        {
            return arr[pivot_idx];
        }
        else if (pivot_idx > target_idx)
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
