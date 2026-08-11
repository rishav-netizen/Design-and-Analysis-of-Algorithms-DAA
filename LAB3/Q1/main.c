#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct Array
{
    int *A;
    int size;
    int length;
} Array;

void Display(const Array *arr);
Array Input(string name);
int BinarySearchIterative(Array arr, int key);
int TernarySearchIterative(Array arr, int key);

int binary_steps = 0;
int ternary_steps = 0;

int main()
{
    Array arr = Input("A");

    Display(&arr);

    int key;
    printf("Enter element you wanna binary search: ");
    scanf("%d", &key);

    int index_ter = TernarySearchIterative(arr, key);
    int index_bin = BinarySearchIterative(arr, key);

    if (index_bin == -1)
        printf("Element not found.\n");
    else
        printf("Element found at index %d\n", index_bin);


    printf("Time steps taken to do binary search: %d\nTime steps taken to do ternary search: %d\n", binary_steps, ternary_steps);
    free(arr.A);

    return 0;
}

int TernarySearchIterative(Array arr, int key)
{
    int l = 0; ternary_steps++;
    int u = arr.length - 1; ternary_steps++;

    while (l <= u)
    {
        ternary_steps++; // loop condition comparison

        int m1 = l + (u-l)/3; ternary_steps++;
        int m2 = u - (u-l)/3; ternary_steps++;

        ternary_steps++;
        if (arr.A[m1] == key)
        {
            return m1;
        }
        
        ternary_steps++;
        if (arr.A[m2] == key)
        {
            return m2;
        }

        ternary_steps++; // the comparison that fails the if block
        if (key < arr.A[m1])
        {
            u = m1 - 1; ternary_steps++;
        }
        else
        {
            ternary_steps++;
            if (key < arr.A[m2])
            {
                l = m1 + 1;ternary_steps++;
                u = m2 - 1; ternary_steps++;
            }
            else
            {
                l = m2 + 1; ternary_steps++;
            }
        }
    }
    ternary_steps++;
    return -1;
}



int BinarySearchIterative(Array arr, int key)
{
    int l = 0; binary_steps++;
    int h = arr.length - 1; binary_steps++;

    while (l <= h)
    {
        binary_steps++;
        int m = (l + h) / 2; binary_steps++;

        binary_steps++;
        if (arr.A[m] == key)
        {
            return m;
        }
        else
        {
            binary_steps++;
            if (arr.A[m] > key)
            {
                h = m - 1; binary_steps++;
            }
            else
            {
                l = m + 1; binary_steps++;
            }
        }
        
    }
    binary_steps++;
    return -1;
}

void Display(const Array *arr)
{
    printf("Elements of the array are: {");

    for (int i = 0; i < arr->length; i++)
    {
        printf("%d", arr->A[i]);

        if (i < arr->length - 1)
            printf(", ");
    }

    printf("}\n");
}

Array Input(string name)
{
    Array arr;

    printf("Enter array %s size: ", name);
    scanf("%d", &arr.size);

    arr.A = (int *)malloc(arr.size * sizeof(int));

    int length;
    printf("Enter the number of numbers: ");
    scanf("%d", &length);

    while (length < 0 || length > arr.size)
    {
        printf("Invalid input! Length must be smaller than size!\n");
        printf("Try again: ");
        scanf("%d", &length);
    }

    arr.length = length;

    for (int i = 0; i < arr.length; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr.A[i]);
    }

    return arr;
}