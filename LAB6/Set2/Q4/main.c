#include <stdio.h>
#include <stdlib.h>

int total_cost = 0;

void Display(int* arr, int n);
void Reverse(int* arr, int i, int j);
void Rotate(int* arr, int i, int mid, int j);
int BinarySearch(int* arr, int start, int end, int val);
void Merge(int* arr, int start, int mid, int end);
void MergeSort(int* arr, int start, int end);

int main()
{
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) return 1;
    
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return 1;
    }
    
    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    printf("Original Array: ");
    Display(arr, n);
    
    MergeSort(arr, 0, n - 1);
    
    printf("Sorted Array: ");
    Display(arr, n);
    
    printf("Total Reversal Cost: %d\n", total_cost);
    
    free(arr);
    return 0;
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

void Reverse(int* arr, int i, int j)
{
    if (i >= j) return;
    total_cost += (j - i + 1);
    while (i < j)
    {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

void Rotate(int* arr, int i, int mid, int j)
{
    if (i > mid || mid >= j) return;
    Reverse(arr, i, mid);
    Reverse(arr, mid + 1, j);
    Reverse(arr, i, j);
}

int BinarySearch(int* arr, int start, int end, int val)
{
    int low = start;
    int high = end;
    int ans = end + 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] >= val)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}

void Merge(int* arr, int start, int mid, int end)
{
    if (start > mid || mid >= end) return;
    
    int m1 = start + (mid - start) / 2;
    int val = arr[m1];
    
    int m2 = BinarySearch(arr, mid + 1, end, val);
    
    int len1 = mid - m1 + 1;
    int len2 = m2 - 1 - mid;
    
    if (len1 > 0 && len2 > 0)
    {
        Rotate(arr, m1, mid, m2 - 1);
    }
    
    Merge(arr, start, m1 - 1, m1 + len2 - 1);
    Merge(arr, m1 + len2 + 1, m2 - 1, end);
}

void MergeSort(int* arr, int start, int end)
{
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);
    Merge(arr, start, mid, end);
}

