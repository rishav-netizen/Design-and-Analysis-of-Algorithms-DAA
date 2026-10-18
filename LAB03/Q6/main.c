#include <stdio.h>
#include <stdlib.h>

static void selectionSort(int array[], int n, int *comparisons, int *swaps)
{
    *comparisons = 0;
    *swaps = 0;

    /* After iteration i, array[0..i] contains the i + 1 smallest values in order. */
    for (int i = 0; i < n - 1; i++)
    {
        int minimumIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            (*comparisons)++;
            if (array[j] < array[minimumIndex])
                minimumIndex = j;
        }

        if (minimumIndex != i)
        {
            int temporary = array[i];
            array[i] = array[minimumIndex];
            array[minimumIndex] = temporary;
            (*swaps)++;
        }
    }
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

    int comparisons;
    int swaps;
    selectionSort(array, n, &comparisons, &swaps);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d%s", array[i], i == n - 1 ? "\n" : " ");
    printf("Comparisons: %d\nSwaps: %d\n", comparisons, swaps);

    free(array);
    return 0;
}
