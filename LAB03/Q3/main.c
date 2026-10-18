#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int min;
    int max;
} MinMax;

static MinMax findMinMax(const int array[], int low, int high, int *comparisons)
{
    if (low == high)
        return (MinMax){array[low], array[low]};

    if (high == low + 1)
    {
        (*comparisons)++;
        return array[low] < array[high]
                   ? (MinMax){array[low], array[high]}
                   : (MinMax){array[high], array[low]};
    }

    int middle = low + (high - low) / 2;
    MinMax left = findMinMax(array, low, middle, comparisons);
    MinMax right = findMinMax(array, middle + 1, high, comparisons);

    (*comparisons)++;
    int minimum = left.min < right.min ? left.min : right.min;
    (*comparisons)++;
    int maximum = left.max > right.max ? left.max : right.max;
    return (MinMax){minimum, maximum};
}

int main(void)
{
    int n;
    printf("Enter array size: ");
    if (scanf("%d", &n) != 1 || n < 1)
        return 1;

    int *array = malloc((size_t)n * sizeof(*array));
    if (array == NULL)
        return 1;

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    int comparisons = 0;
    MinMax result = findMinMax(array, 0, n - 1, &comparisons);
    printf("Minimum = %d\nMaximum = %d\n", result.min, result.max);
    printf("Comparisons = %d\n", comparisons);

    free(array);
    return 0;
}
