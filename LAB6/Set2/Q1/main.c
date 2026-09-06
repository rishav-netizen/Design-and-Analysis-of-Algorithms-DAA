#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

void Display(int* arr, int n);
int FindMax(int* arr, int n);
void FindFirstSecondLargest(int* arr, int n, int* first, int* second);
double FindMean(int* arr, int n);
void Swap(int* a, int* b);
int Partition(int* arr, int low, int high);
void QuickSort(int* arr, int low, int high);
double FindMedian(int* arr, int n);
double FindStandardDeviation(int* arr, int n);
int FindMode(int* arr, int n);
int RemoveDuplicates(int* arr, int n);
void ReverseArray(int* arr, int n);
void PartitionRandomPivot(int* arr, int n);
void PrintMenu();

int main()
{
    srand(time(NULL));
    int n;
    printf("Enter number of elements in array: ");
    while (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input. Please enter a positive integer: ");
        while(getchar() != '\n');
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return 1;
    }

    int input_choice;
    printf("Choose input method:\n1. Manual Input\n2. Random Generation\nEnter choice: ");
    while (scanf("%d", &input_choice) != 1 || (input_choice != 1 && input_choice != 2))
    {
        printf("Invalid input. Enter 1 or 2: ");
        while(getchar() != '\n');
    }

    if (input_choice == 1)
    {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++)
        {
            while (scanf("%d", &arr[i]) != 1)
            {
                printf("Invalid input. Enter integer %d: ", i + 1);
                while(getchar() != '\n');
            }
        }
    }
    else
    {
        int range;
        printf("Enter max value for random integers: ");
        scanf("%d", &range);
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % (range + 1);
        }
        printf("Generated array: ");
        Display(arr, n);
    }

    int choice;
    int current_n = n;
    do
    {
        PrintMenu();
        if (scanf("%d", &choice) != 1)
        {
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                if (current_n == 0) printf("Array is empty.\n");
                else printf("Maximum element: %d\n", FindMax(arr, current_n));
                break;
            case 2:
                if (current_n < 2)
                {
                    printf("Array has less than 2 elements.\n");
                }
                else
                {
                    int first, second;
                    FindFirstSecondLargest(arr, current_n, &first, &second);
                    if (second == INT_MIN)
                    {
                        printf("No second largest element found.\n");
                    }
                    else
                    {
                        printf("1st Largest: %d, 2nd Largest: %d\n", first, second);
                    }
                }
                break;
            case 3:
                if (current_n == 0) printf("Array is empty.\n");
                else printf("Mean: %.2f\n", FindMean(arr, current_n));
                break;
            case 4:
                if (current_n == 0) printf("Array is empty.\n");
                else printf("Median: %.2f\n", FindMedian(arr, current_n));
                break;
            case 5:
                if (current_n == 0) printf("Array is empty.\n");
                else printf("Standard Deviation: %.2f\n", FindStandardDeviation(arr, current_n));
                break;
            case 6:
                if (current_n == 0) printf("Array is empty.\n");
                else printf("Mode: %d\n", FindMode(arr, current_n));
                break;
            case 7:
                current_n = RemoveDuplicates(arr, current_n);
                printf("Array after removing duplicates: ");
                Display(arr, current_n);
                break;
            case 8:
                ReverseArray(arr, current_n);
                printf("Array after reversing: ");
                Display(arr, current_n);
                break;
            case 9:
                PartitionRandomPivot(arr, current_n);
                printf("Array after partitioning: ");
                Display(arr, current_n);
                break;
            case 10:
                Display(arr, current_n);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    free(arr);
    return 0;
}

void Display(int* arr, int n)
{
    printf("{");
    for(int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if(i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

int FindMax(int* arr, int n)
{
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

void FindFirstSecondLargest(int* arr, int n, int* first, int* second)
{
    *first = arr[0];
    *second = INT_MIN;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *first)
        {
            *second = *first;
            *first = arr[i];
        }
        else if (arr[i] > *second && arr[i] != *first)
        {
            *second = arr[i];
        }
    }
}

double FindMean(int* arr, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum / n;
}

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int* arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QuickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

double FindMedian(int* arr, int n)
{
    int* temp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }
    QuickSort(temp, 0, n - 1);
    double median;
    if (n % 2 == 0)
    {
        median = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else
    {
        median = temp[n / 2];
    }
    free(temp);
    return median;
}

double FindStandardDeviation(int* arr, int n)
{
    double mean = FindMean(arr, n);
    double variance_sum = 0;
    for (int i = 0; i < n; i++)
    {
        variance_sum += pow(arr[i] - mean, 2);
    }
    return sqrt(variance_sum / n);
}

int FindMode(int* arr, int n)
{
    int* temp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        temp[i] = arr[i];
    }
    QuickSort(temp, 0, n - 1);
    
    int mode = temp[0];
    int max_count = 1;
    int current_count = 1;
    
    for (int i = 1; i < n; i++)
    {
        if (temp[i] == temp[i - 1])
        {
            current_count++;
        }
        else
        {
            if (current_count > max_count)
            {
                max_count = current_count;
                mode = temp[i - 1];
            }
            current_count = 1;
        }
    }
    if (current_count > max_count)
    {
        mode = temp[n - 1];
    }
    
    free(temp);
    return mode;
}

int RemoveDuplicates(int* arr, int n)
{
    int unique_count = 0;
    for (int i = 0; i < n; i++)
    {
        int is_duplicate = 0;
        for (int j = 0; j < unique_count; j++)
        {
            if (arr[i] == arr[j])
            {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate)
        {
            arr[unique_count] = arr[i];
            unique_count++;
        }
    }
    return unique_count;
}

void ReverseArray(int* arr, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

void PartitionRandomPivot(int* arr, int n)
{
    if (n <= 1) return;
    int pivot_idx = rand() % n;
    int pivot = arr[pivot_idx];
    
    int temp = arr[pivot_idx];
    arr[pivot_idx] = arr[n - 1];
    arr[n - 1] = temp;
    
    int i = -1;
    for (int j = 0; j < n - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[n - 1];
    arr[n - 1] = temp;
    
    printf("Pivot element %d randomly chosen and placed at index %d\n", pivot, i + 1);
}

void PrintMenu()
{
    printf("\n--- 1D Array Operations ---\n");
    printf("1. Find Maximum\n");
    printf("2. Find 1st and 2nd Largest\n");
    printf("3. Find Mean\n");
    printf("4. Find Median\n");
    printf("5. Find Standard Deviation\n");
    printf("6. Find Mode\n");
    printf("7. Remove Duplicates\n");
    printf("8. Reverse Array\n");
    printf("9. Partition with Random Pivot\n");
    printf("10. Display Array\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

