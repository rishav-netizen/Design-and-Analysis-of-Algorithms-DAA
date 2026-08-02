#include <stdio.h>
#include <stdlib.h>

void Display(int *array, int length);
int BinarySearch(int *array, int length, int key);

int main(){
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    
    int o_count;
    printf("Enter the number of ones: ");
    scanf("%d", &o_count);

    // Dynamic allocation so that the zeroes are already there
    int *binary_array;
    binary_array = (int *)malloc(n * sizeof(int));


    for (int i = n - o_count; i < n; i++)
    {
        binary_array[i] = 1;
    }
    
    Display(binary_array, n);
    
    // since array is sorted we do binary search
    int partition_index = BinarySearch(binary_array, n, 1);
    printf("Index of partition is: %d\n", partition_index);
    
    return 0;
}

int BinarySearch(int *array, int length, int key)
{   
    int l = 0, u = length - 1, m = (l + u) / 2;
    while (l < u)
    {
        m = (l + u) / 2;
        if (array[m] == key)
            return m;
        else if (array[m] < key)
            l = m + 1;
        else
            u = m - 1;
    }
    return -1; // key not found
}   

void Display(int *array, int length)
{
    printf("{");
    for (int i = 0; i < length; i++)
    {
        printf("%d", array[i]);
        if(i < length - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}