#include <stdio.h>
#include <stdlib.h>

void Display(int *array, int length);
int BinarySearch(int *array, int length, int key);

int main()
{
    int n;
    printf("Enter the size of array: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid Input! Try again: ");
        scanf("%d", &n);
    }
    printf("\n");
    
    
    int o_count;
    printf("Enter the number of ones: ");
    scanf("%d", &o_count);
    while ((o_count < 0) || (o_count > n))
    {
        printf("Invalid Input! Try again: ");
        scanf("%d", &o_count);
    }
    printf("\n");
    

    // dynamic allocation so that the zeroes are already there
    int *binary_array;
    binary_array = (int *)calloc(n, sizeof(int));

    for (int i = n - o_count; i < n; i++)
    {
        binary_array[i] = 1;
    }
    
    printf("Array: ");
    Display(binary_array, n);

    if ((o_count == 0) || (o_count == n))
    {
        printf("No partition point exists!\n");
        return 1;
    }

    // since array is sorted we do binary search (a little modified)
    int partition_index = BinarySearch(binary_array, n, 1);
    printf("Index of partition is: %d\n", partition_index);

    free(binary_array);
    
    return 0;
}

int BinarySearch(int *array, int length, int key)
{   
    int l = 0, u = length - 1, m = (l + u) / 2;
    int index = -1;
    while (l < u)
    {
        m = (l + u) / 2;
        if (array[m] == key)
        {
            index = m; // not confirm that its the first occurrence of the key i.e. 1
            u = m - 1; // so we keep searching left side because it starts with zeros
        }
        else
        {
            l = m + 1;
        }
    }
    return index;
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