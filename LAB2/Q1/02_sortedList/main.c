#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* A dictionary implemented with a fixed-capacity sorted array. */
typedef struct
{
    int *A;
    int size;
    int length;
} Dict;

/* Function prototypes */
void Input(Dict *D);
void Display(const Dict *D);
int Search(const Dict *D, int key);
bool Insert(Dict *D, int key);
bool Delete(Dict *D, int key);
bool Max(const Dict *D, int *value);
bool Min(const Dict *D, int *value);
bool Predecessor(const Dict *D, int index, int *value);
bool Successor(const Dict *D, int index, int *value);

static int LowerBound(const Dict *D, int key);

int main(void)
{
    Dict D;
    int capacity;
    int key;
    int value;

    printf("Enter maximum dictionary size: ");
    if (scanf("%d", &capacity) != 1 || capacity <= 0)
    {
        printf("Dictionary size must be a positive integer.\n");
        return 1;
    }

    D.size = capacity;
    D.length = 0;
    D.A = malloc((size_t)D.size * sizeof *D.A);

    if (D.A == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    Input(&D);

    printf("\nSorted dictionary:\n");
    Display(&D);

    printf("\nEnter element to insert: ");
    if (scanf("%d", &key) == 1)
        Insert(&D, key);

    printf("Dictionary after insertion: ");
    Display(&D);

    printf("\nEnter key to search: ");
    if (scanf("%d", &key) == 1)
    {
        int position = Search(&D, key);

        if (position == -1)
            printf("Key not found.\n");
        else
            printf("Key found at index %d.\n", position);
    }

    if (Max(&D, &value))
        printf("\nMaximum = %d\n", value);
    else
        printf("\nMaximum does not exist: dictionary is empty.\n");

    if (Min(&D, &value))
        printf("Minimum = %d\n", value);
    else
        printf("Minimum does not exist: dictionary is empty.\n");

    printf("\nEnter an existing key to find predecessor and successor: ");
    if (scanf("%d", &key) == 1)
    {
        int position = Search(&D, key);

        if (position == -1)
            printf("Key not found.\n");
        else
        {
            if (Predecessor(&D, position, &value))
                printf("Predecessor = %d\n", value);
            else
                printf("No predecessor exists.\n");

            if (Successor(&D, position, &value))
                printf("Successor = %d\n", value);
            else
                printf("No successor exists.\n");
        }
    }

    printf("\nEnter key to delete: ");
    if (scanf("%d", &key) == 1)
    {
        if (Delete(&D, key))
            printf("Key deleted successfully.\n");
        else
            printf("Key not found.\n");
    }

    printf("\nDictionary after deletion:\n");
    Display(&D);

    free(D.A);
    return 0;
}

/* Reads unique keys. Insert keeps the array sorted after every input. */
void Input(Dict *D)
{
    int count;
    int key;

    do
    {
        printf("Enter number of initial elements (0-%d): ", D->size);
        if (scanf("%d", &count) != 1)
            return;
    } while (count < 0 || count > D->size);

    for (int i = 0; i < count;)
    {
        printf("Enter element %d: ", i + 1);

        if (scanf("%d", &key) != 1)
            return;

        if (Insert(D, key))
            i++;
    }
}

void Display(const Dict *D)
{
    printf("{ ");

    for (int i = 0; i < D->length; i++)
    {
        printf("%d", D->A[i]);

        if (i < D->length - 1)
            printf(", ");
    }

    printf(" }\n");
}

/* Returns the first index whose value is greater than or equal to key. */
static int LowerBound(const Dict *D, int key)
{
    int low = 0;
    int high = D->length;

    while (low < high)
    {
        int mid = low + (high - low) / 2;

        if (D->A[mid] < key)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

/* Binary search: returns the key index, or -1 when the key is absent. */
int Search(const Dict *D, int key)
{
    int index = LowerBound(D, key);

    if (index < D->length && D->A[index] == key)
        return index;

    return -1;
}

/* Inserts a unique key at its sorted position. */
bool Insert(Dict *D, int key)
{
    if (D->length == D->size)
    {
        printf("Dictionary is full.\n");
        return false;
    }

    int index = LowerBound(D, key);

    if (index < D->length && D->A[index] == key)
    {
        printf("Duplicate keys are not allowed.\n");
        return false;
    }

    for (int i = D->length; i > index; i--)
        D->A[i] = D->A[i - 1];

    D->A[index] = key;
    D->length++;
    return true;
}

/* Deletes key after locating it with binary search. */
bool Delete(Dict *D, int key)
{
    int index = Search(D, key);

    if (index == -1)
        return false;

    for (int i = index; i < D->length - 1; i++)
        D->A[i] = D->A[i + 1];

    D->length--;
    return true;
}

bool Max(const Dict *D, int *value)
{
    if (D->length == 0)
        return false;

    *value = D->A[D->length - 1];
    return true;
}

bool Min(const Dict *D, int *value)
{
    if (D->length == 0)
        return false;

    *value = D->A[0];
    return true;
}

/* Given an item index, its predecessor is at the previous array position. */
bool Predecessor(const Dict *D, int index, int *value)
{
    if (index <= 0 || index >= D->length)
        return false;

    *value = D->A[index - 1];
    return true;
}

/* Given an item index, its successor is at the next array position. */
bool Successor(const Dict *D, int index, int *value)
{
    if (index < 0 || index >= D->length - 1)
        return false;

    *value = D->A[index + 1];
    return true;
}
