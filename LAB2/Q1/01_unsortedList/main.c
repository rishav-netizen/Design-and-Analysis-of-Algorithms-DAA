#include <stdio.h>
#include <stdlib.h>

typedef struct Dict
{
    int *A;
    int size;
    int length;
} Dict;

// Function Prototypes
void Input(Dict *D);
void Display(Dict D);
void Insert(Dict *D, int x);
int Search(Dict *D, int key);
void Delete(Dict *D, int key);
int Max(Dict *D);
int Min(Dict *D);
int Predecessor(Dict *D, int key);
int Successor(Dict *D, int key);

int main()
{
    Dict D;
    int n, key;

    printf("Enter size of dictionary: ");
    scanf("%d", &n);

    D.size = n;
    D.length = 0;
    D.A = (int *)malloc(n * sizeof(int));

    Input(&D);

    printf("\nDictionary:\n");
    Display(D);

    printf("\nEnter element to insert: ");
    scanf("%d", &key);
    Insert(&D, key);

    Display(D);

    printf("\nEnter key to search: ");
    scanf("%d", &key);

    int pos = Search(&D, key);
    if (pos != -1)
        printf("Key found at index %d\n", pos);
    else
        printf("Key not found.\n");

    printf("\nMaximum = %d\n", Max(&D));
    printf("Minimum = %d\n", Min(&D));

    printf("\nEnter key to find predecessor and successor: ");
    scanf("%d", &key);

    int pre = Predecessor(&D, key);
    int suc = Successor(&D, key);

    if (pre == -1)
        printf("No predecessor exists.\n");
    else
        printf("Predecessor = %d\n", pre);

    if (suc == -1)
        printf("No successor exists.\n");
    else
        printf("Successor = %d\n", suc);

    printf("\nEnter key to delete: ");
    scanf("%d", &key);

    Delete(&D, key);

    printf("\nDictionary after deletion:\n");
    Display(D);

    free(D.A);

    return 0;
}

// Input elements
void Input(Dict *D)
{
    int len;

    printf("Enter number of elements: ");
    scanf("%d", &len);

    while (len < 0 || len > D->size)
    {
        printf("Invalid input! Enter again: ");
        scanf("%d", &len);
    }

    D->length = len;

    for (int i = 0; i < len; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &D->A[i]);
    }
}

// Display dictionary
void Display(Dict D)
{
    printf("{ ");

    for (int i = 0; i < D.length; i++)
    {
        printf("%d", D.A[i]);

        if (i != D.length - 1)
            printf(", ");
    }

    printf(" }\n");
}

// Insert at end
void Insert(Dict *D, int x)
{
    if (D->length == D->size)
    {
        printf("Dictionary Full!\n");
        return;
    }

    D->A[D->length++] = x;
}

// Linear Search
int Search(Dict *D, int key)
{
    for (int i = 0; i < D->length; i++)
    {
        if (D->A[i] == key)
            return i;
    }

    return -1;
}

// Delete element by key
void Delete(Dict *D, int key)
{
    int index = Search(D, key);

    if (index == -1)
    {
        printf("Key not found.\n");
        return;
    }

    for (int i = index; i < D->length - 1; i++)
        D->A[i] = D->A[i + 1];

    D->length--;
}

// Maximum element
int Max(Dict *D)
{
    if (D->length == 0)
        return -1;

    int max = D->A[0];

    for (int i = 1; i < D->length; i++)
    {
        if (D->A[i] > max)
            max = D->A[i];
    }

    return max;
}

// Minimum element
int Min(Dict *D)
{
    if (D->length == 0)
        return -1;

    int min = D->A[0];

    for (int i = 1; i < D->length; i++)
    {
        if (D->A[i] < min)
            min = D->A[i];
    }

    return min;
}

// Largest element smaller than key
int Predecessor(Dict *D, int key)
{
    int pred = -1;

    for (int i = 0; i < D->length; i++)
    {
        if (D->A[i] < key)
        {
            if (pred == -1 || D->A[i] > pred)
                pred = D->A[i];
        }
    }

    return pred;
}

// Smallest element greater than key
int Successor(Dict *D, int key)
{
    int succ = -1;

    for (int i = 0; i < D->length; i++)
    {
        if (D->A[i] > key)
        {
            if (succ == -1 || D->A[i] < succ)
                succ = D->A[i];
        }
    }

    return succ;
}
