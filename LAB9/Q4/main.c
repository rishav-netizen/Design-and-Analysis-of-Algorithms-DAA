#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int size;
    int capacity;
    long long *array;
} MinHeap;

MinHeap *createMinHeap(int capacity);
void swapLong(long long *a, long long *b);
void minHeapify(MinHeap *heap, int idx);
long long extractMin(MinHeap *heap);
void insertMinHeap(MinHeap *heap, long long val);
int randomBtw(int l, int u);
void fillSticksRandomly(int n, long long *sticks, int l, int u);
void displaySticks(int n, long long *sticks);

int main() {
    int n;
    printf("Enter the number of sticks: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input try again: ");
        scanf("%d", &n);
    }

    long long *sticks = (long long *)malloc(n * sizeof(long long));

    int choice;
    printf("Do you wanna: \t(0) Enter stick lengths manually or\n\t\t(1) Have them randomly filled?\nChoice: ");
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
            printf("Enter %d positive stick lengths: ", n);
            for (int i = 0; i < n; i++)
            {
                scanf("%lld", &sticks[i]);
                while (sticks[i] <= 0)
                {
                    printf("Lengths must be positive. Re-enter stick %d: ", i + 1);
                    scanf("%lld", &sticks[i]);
                }
            }
            break;
        }

        case 1:
        {
            int l, u;
            printf("Enter the lower and upper limits for stick lengths: ");
            scanf("%d %d", &l, &u);
            while (l <= 0 || l >= u)
            {
                printf("Invalid limits (ensure 0 < l < u). Re-enter: ");
                scanf("%d %d", &l, &u);
            }
            fillSticksRandomly(n, sticks, l, u);
            break;
        }

        default:
            break;
    }

    printf("Initial sticks: ");
    displaySticks(n, sticks);

    if (n == 1)
    {
        printf("\nOnly 1 stick present. No connection needed.\n");
        printf("Total Minimum Cost: 0\n");
        free(sticks);
        return 0;
    }

    MinHeap *heap = createMinHeap(n);
    for (int i = 0; i < n; i++)
    {
        heap->array[i] = sticks[i];
    }
    heap->size = n;

    /* Build min-heap in O(n) */
    for (int i = (heap->size - 1) / 2; i >= 0; i--)
    {
        minHeapify(heap, i);
    }

    printf("\n================ STEP-BY-STEP MERGE LOG ================\n");
    printf("+------+------------+------------+------------+----------------+\n");
    printf("| Step |  Stick A   |  Stick B   | Merge Cost | Cumulative Cost|\n");
    printf("+------+------------+------------+------------+----------------+\n");

    long long totalCost = 0;
    int step = 1;

    while (heap->size > 1)
    {
        long long first = extractMin(heap);
        long long second = extractMin(heap);
        long long mergeCost = first + second;
        totalCost += mergeCost;

        printf("| %4d | %10lld | %10lld | %10lld | %14lld |\n",
               step++, first, second, mergeCost, totalCost);

        insertMinHeap(heap, mergeCost);
    }

    long long finalStick = extractMin(heap);

    printf("+------+------------+------------+------------+----------------+\n");
    printf("Final Combined Stick Length : %lld\n", finalStick);
    printf("Minimum Total Connection Cost: %lld\n", totalCost);
    printf("========================================================\n");

    free(sticks);
    free(heap->array);
    free(heap);
    return 0;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (long long *)malloc(capacity * sizeof(long long));
    return heap;
}

void swapLong(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left] < heap->array[smallest])
    {
        smallest = left;
    }

    if (right < heap->size && heap->array[right] < heap->array[smallest])
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        swapLong(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

long long extractMin(MinHeap *heap)
{
    if (heap->size <= 0) return 0;
    long long root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

void insertMinHeap(MinHeap *heap, long long val)
{
    heap->size++;
    int i = heap->size - 1;
    while (i > 0 && val < heap->array[(i - 1) / 2])
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

void fillSticksRandomly(int n, long long *sticks, int l, int u)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        sticks[i] = randomBtw(l, u);
    }
}

void displaySticks(int n, long long *sticks)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%lld", sticks[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}
