#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *fillArray(int size);
int BinarySearchIterative(const int array[], int size, int key, int *steps);
int TernarySearchIterative(const int array[], int size, int key, int *steps);
double average(const int values[], int length);
int compareKeys(int left, int right);

static int compareIntegers(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;
    return (a > b) - (a < b);
}

int main(void)
{
    srand((unsigned int)time(NULL));

    const int sizes[] = {10, 100, 1000, 3000, 5000, 10000};
    const int sizesLength = (int)(sizeof(sizes) / sizeof(sizes[0]));

    printf("Size\tBinary avg. comparisons\tTernary avg. comparisons\n");

    for (int sizeIndex = 0; sizeIndex < sizesLength; sizeIndex++)
    {
        const int currentSize = sizes[sizeIndex];
        int *array = fillArray(currentSize);
        int *binarySteps = calloc((size_t)currentSize, sizeof(*binarySteps));
        int *ternarySteps = calloc((size_t)currentSize, sizeof(*ternarySteps));

        if (array == NULL || binarySteps == NULL || ternarySteps == NULL)
        {
            fprintf(stderr, "Could not allocate memory for size %d.\n", currentSize);
            free(array);
            free(binarySteps);
            free(ternarySteps);
            return EXIT_FAILURE;
        }

        /* Binary and ternary search require a sorted array. */
        qsort(array, (size_t)currentSize, sizeof(*array), compareIntegers);

        /* Save the step count for each individual search at the same index. */
        for (int i = 0; i < currentSize; i++)
        {
            BinarySearchIterative(array, currentSize, array[i], &binarySteps[i]);
            TernarySearchIterative(array, currentSize, array[i], &ternarySteps[i]);
        }

        printf("%d\t%.2f\t\t\t%.2f\n",
               currentSize,
               average(binarySteps, currentSize),
               average(ternarySteps, currentSize));

        free(array);
        free(binarySteps);
        free(ternarySteps);
    }

    return EXIT_SUCCESS;
}

int *fillArray(int size)
{
    int *array = malloc((size_t)size * sizeof(*array));

    if (array == NULL)
        return NULL;

    /* Distinct values ensure that duplicate blocks do not affect the result. */
    for (int i = 0; i < size; i++)
        array[i] = i + 1;

    /* Shuffle before qsort so the input is genuinely unsorted. */
    for (int i = size - 1; i > 0; i--)
    {
        int randomIndex = rand() % (i + 1);
        int temporary = array[i];
        array[i] = array[randomIndex];
        array[randomIndex] = temporary;
    }

    return array;
}

/* One three-way key comparison: negative, zero, or positive. */
int compareKeys(int left, int right)
{
    return (left > right) - (left < right);
}

int BinarySearchIterative(const int array[], int size, int key, int *steps)
{
    int l = 0;
    int h = size - 1;
    *steps = 0;

    while (l <= h)
    {
        int m = l + (h - l) / 2;
        (*steps)++;
        int comparison = compareKeys(key, array[m]);

        if (comparison == 0)
            return m;
        if (comparison < 0)
            h = m - 1;
        else
            l = m + 1;
    }

    return -1;
}

int TernarySearchIterative(const int array[], int size, int key, int *steps)
{
    int l = 0;
    int u = size - 1;
    *steps = 0;

    while (l <= u)
    {
        int m1 = l + (u - l) / 3;
        int m2 = u - (u - l) / 3;

        (*steps)++;
        int firstComparison = compareKeys(key, array[m1]);
        if (firstComparison == 0)
            return m1;

        (*steps)++;
        int secondComparison = compareKeys(key, array[m2]);
        if (secondComparison == 0)
            return m2;

        if (firstComparison < 0)
            u = m1 - 1;
        else if (secondComparison > 0)
            l = m2 + 1;
        else
        {
            l = m1 + 1;
            u = m2 - 1;
        }
    }
    return -1;
}

double average(const int values[], int length)
{
    long long total = 0;

    for (int i = 0; i < length; i++)
        total += values[i];

    return (double)total / length;
}
