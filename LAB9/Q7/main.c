#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int size;
    int capacity;
    int *array;
} MaxHeap;

MaxHeap *createMaxHeap(int capacity);
void swapInt(int *a, int *b);
void maxHeapify(MaxHeap *heap, int idx);
int extractMax(MaxHeap *heap);
void insertMaxHeap(MaxHeap *heap, int val);
int randomBtw(int l, int u);
void fillArrayRandomly(int n, int *arr, int l, int u);
void displayArray(int n, int *arr);

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input try again: ");
        scanf("%d", &n);
    }

    int *arr = (int *)malloc(n * sizeof(int));

    int choice;
    printf("Do you wanna: \t(0) Enter array elements manually or\n\t\t(1) Have it randomly filled?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1)
    {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    switch (choice)
    {
        case 0:
        {
            printf("Enter %d positive integers: ", n);
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
                while (arr[i] <= 0)
                {
                    printf("Elements must be positive. Re-enter element %d: ", i + 1);
                    scanf("%d", &arr[i]);
                }
            }
            break;
        }

        case 1:
        {
            int l, u;
            printf("Enter lower and upper limits for random numbers: ");
            scanf("%d %d", &l, &u);
            while (l <= 0 || l >= u)
            {
                printf("Invalid limits (ensure 0 < l < u). Re-enter: ");
                scanf("%d %d", &l, &u);
            }
            fillArrayRandomly(n, arr, l, u);
            break;
        }

        default:
            break;
    }

    printf("\nInitial input array: ");
    displayArray(n, arr);

    if (n == 1)
    {
        printf("\nSingle element array. Deviation is trivially 0.\n");
        free(arr);
        return 0;
    }

    /* Step 1: Pre-process elements: multiply odd numbers by 2 to reach their maximum potential */
    MaxHeap *heap = createMaxHeap(n + 5);
    int minVal = 2147483647;

    for (int i = 0; i < n; i++)
    {
        int val = arr[i];
        if (val % 2 != 0)
        {
            val *= 2;
        }
        heap->array[i] = val;
        if (val < minVal)
        {
            minVal = val;
        }
    }
    heap->size = n;

    /* Build max-heap */
    for (int i = (heap->size - 1) / 2; i >= 0; i--)
    {
        maxHeapify(heap, i);
    }

    int minDeviation = heap->array[0] - minVal;

    printf("\nAfter doubling all odds (upper-bound initialization):\n");
    printf("Initial Max: %d | Initial Min: %d | Starting Deviation: %d\n",
           heap->array[0], minVal, minDeviation);

    printf("\n================ STEP-BY-STEP DEVIATION REDUCTION ================\n");
    printf("+------+-------------+-------------+-------------------+----------------------------+\n");
    printf("| Step | Current Max | Current Min | Current Deviation | Action Taken               |\n");
    printf("+------+-------------+-------------+-------------------+----------------------------+\n");

    int step = 1;

    while (heap->size > 0)
    {
        int currentMax = extractMax(heap);
        int currentDev = currentMax - minVal;

        if (currentDev < minDeviation)
        {
            minDeviation = currentDev;
        }

        if (currentMax % 2 == 0)
        {
            int halved = currentMax / 2;
            if (halved < minVal)
            {
                minVal = halved;
            }
            insertMaxHeap(heap, halved);

            char actionStr[64];
            snprintf(actionStr, sizeof(actionStr), "Halved %d -> %d, reinserted", currentMax, halved);
            printf("| %4d | %11d | %11d | %17d | %-26s |\n",
                   step++, currentMax, minVal, currentDev, actionStr);
        }
        else
        {
            /* Top is odd; cannot be divided further */
            printf("| %4d | %11d | %11d | %17d | %-26s |\n",
                   step++, currentMax, minVal, currentDev, "Max is odd; stopping search");
            break;
        }
    }

    printf("+------+-------------+-------------+-------------------+----------------------------+\n");
    printf("\n======================= FINAL RESULT =======================\n");
    printf("Minimum Achievable Deviation: %d\n", minDeviation);
    printf("============================================================\n");

    free(arr);
    free(heap->array);
    free(heap);
    return 0;
}

MaxHeap *createMaxHeap(int capacity)
{
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (int *)malloc(capacity * sizeof(int));
    return heap;
}

void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap *heap, int idx)
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left] > heap->array[largest])
    {
        largest = left;
    }

    if (right < heap->size && heap->array[right] > heap->array[largest])
    {
        largest = right;
    }

    if (largest != idx)
    {
        swapInt(&heap->array[largest], &heap->array[idx]);
        maxHeapify(heap, largest);
    }
}

int extractMax(MaxHeap *heap)
{
    if (heap->size <= 0) return 0;
    int root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
    return root;
}

void insertMaxHeap(MaxHeap *heap, int val)
{
    heap->size++;
    int i = heap->size - 1;
    while (i > 0 && val > heap->array[(i - 1) / 2])
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = val;
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}

void fillArrayRandomly(int n, int *arr, int l, int u)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = randomBtw(l, u);
    }
}

void displayArray(int n, int *arr)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}
