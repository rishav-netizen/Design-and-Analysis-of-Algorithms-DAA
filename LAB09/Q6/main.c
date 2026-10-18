#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char ch;
    int freq;
} CharFreq;

typedef struct {
    int size;
    int capacity;
    CharFreq *array;
} MaxHeap;

typedef struct {
    CharFreq item;
    int releaseTime;
} CooldownItem;

typedef struct {
    int front;
    int rear;
    int count;
    int capacity;
    CooldownItem *array;
} Queue;

MaxHeap *createMaxHeap(int capacity);
void swapCharFreq(CharFreq *a, CharFreq *b);
void maxHeapify(MaxHeap *heap, int idx);
void insertMaxHeap(MaxHeap *heap, CharFreq elem);
CharFreq extractMax(MaxHeap *heap);

Queue *createQueue(int capacity);
void enqueue(Queue *q, CooldownItem item);
CooldownItem dequeue(Queue *q);
int isQueueEmpty(Queue *q);

int validateResult(const char *str, int k);
int randomBtw(int l, int u);
void fillStringRandomly(char *str, int n, int alphabetSize);

int main() {
    int choice;
    printf("Do you wanna: \t(0) Enter string manually or\n\t\t(1) Have it randomly generated?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1)
    {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    char inputStr[1024];

    switch (choice)
    {
        case 0:
        {
            printf("Enter the input string (no spaces): ");
            scanf("%1023s", inputStr);
            break;
        }

        case 1:
        {
            int len, alphabetSize;
            printf("Enter desired string length: ");
            scanf("%d", &len);
            while (len <= 0 || len > 1000)
            {
                printf("Invalid length (1 to 1000). Re-enter: ");
                scanf("%d", &len);
            }

            printf("Enter distinct character alphabet pool size (2 to 26): ");
            scanf("%d", &alphabetSize);
            while (alphabetSize < 2 || alphabetSize > 26)
            {
                printf("Invalid alphabet size. Re-enter: ");
                scanf("%d", &alphabetSize);
            }

            fillStringRandomly(inputStr, len, alphabetSize);
            printf("Generated random string: \"%s\"\n", inputStr);
            break;
        }

        default:
            break;
    }

    int k;
    printf("Enter distance separation constraint (K): ");
    scanf("%d", &k);
    while (k < 0)
    {
        printf("K must be non-negative. Re-enter K: ");
        scanf("%d", &k);
    }

    int n = (int)strlen(inputStr);
    printf("\nInput String  : \"%s\" (Length: %d)\n", inputStr, n);
    printf("Constraint K  : %d\n", k);

    if (k <= 1 || n <= 1)
    {
        printf("\nResulting String: \"%s\"\n", inputStr);
        printf("Validation: Valid (Trivially satisfied for K <= 1).\n");
        return 0;
    }

    /* Count character frequencies */
    int count[256] = {0};
    for (int i = 0; i < n; i++)
    {
        count[(unsigned char)inputStr[i]]++;
    }

    /* Count distinct characters */
    int distinct = 0;
    for (int i = 0; i < 256; i++)
    {
        if (count[i] > 0)
        {
            distinct++;
        }
    }

    MaxHeap *heap = createMaxHeap(distinct + 10);
    for (int i = 0; i < 256; i++)
    {
        if (count[i] > 0)
        {
            CharFreq cf;
            cf.ch = (char)i;
            cf.freq = count[i];
            insertMaxHeap(heap, cf);
        }
    }

    char *result = (char *)malloc((n + 1) * sizeof(char));
    Queue *cooldownQueue = createQueue(k + 10);

    int possible = 1;
    printf("\n================ STEP-BY-STEP GREEDY PLACEMENT ================\n");
    printf("+-------+----------+-------------------+----------------------+\n");
    printf("| Index | Selected | Remaining In Heap | Cooldown Queue State |\n");
    printf("+-------+----------+-------------------+----------------------+\n");

    for (int i = 0; i < n; i++)
    {
        /* Release items from cooldown whose cooldown horizon has elapsed:
           If an item was placed at index p, it can only be placed again at index >= p + k. */
        while (!isQueueEmpty(cooldownQueue) && cooldownQueue->array[cooldownQueue->front].releaseTime <= i)
        {
            CooldownItem released = dequeue(cooldownQueue);
            insertMaxHeap(heap, released.item);
        }

        if (heap->size == 0)
        {
            /* All remaining characters are currently locked in cooldown */
            possible = 0;
            break;
        }

        CharFreq best = extractMax(heap);
        result[i] = best.ch;

        best.freq--;
        if (best.freq > 0)
        {
            CooldownItem cd;
            cd.item = best;
            cd.releaseTime = i + k;
            enqueue(cooldownQueue, cd);
        }

        printf("| %5d |    '%c'   | %17d | %20d |\n",
               i, result[i], heap->size, cooldownQueue->count);
    }

    result[n] = '\0';
    printf("+-------+----------+-------------------+----------------------+\n");

    if (possible)
    {
        printf("\n======================= REORGANIZATION SUMMARY =======================\n");
        printf("Status            : SUCCESSFUL REORGANIZATION\n");
        printf("Reorganized String: \"%s\"\n", result);
        int valid = validateResult(result, k);
        printf("Validation Check  : %s\n", valid ? "VERIFIED (Distance condition holds for all pairs)" : "FAILED");
        printf("======================================================================\n");
    }
    else
    {
        printf("\n======================= REORGANIZATION SUMMARY =======================\n");
        printf("Status            : IMPOSSIBLE (Violates Pigeonhole / Distance Bound)\n");
        printf("Reorganized String: \"\" (Empty string returned)\n");
        printf("======================================================================\n");
    }

    free(result);
    free(heap->array);
    free(heap);
    free(cooldownQueue->array);
    free(cooldownQueue);

    return 0;
}

MaxHeap *createMaxHeap(int capacity)
{
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (CharFreq *)malloc(capacity * sizeof(CharFreq));
    return heap;
}

void swapCharFreq(CharFreq *a, CharFreq *b)
{
    CharFreq temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap *heap, int idx)
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].freq > heap->array[largest].freq)
    {
        largest = left;
    }

    if (right < heap->size && heap->array[right].freq > heap->array[largest].freq)
    {
        largest = right;
    }

    if (largest != idx)
    {
        swapCharFreq(&heap->array[largest], &heap->array[idx]);
        maxHeapify(heap, largest);
    }
}

void insertMaxHeap(MaxHeap *heap, CharFreq elem)
{
    heap->size++;
    int i = heap->size - 1;
    while (i > 0 && elem.freq > heap->array[(i - 1) / 2].freq)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = elem;
}

CharFreq extractMax(MaxHeap *heap)
{
    CharFreq nullItem;
    nullItem.ch = '\0';
    nullItem.freq = 0;
    if (heap->size <= 0) return nullItem;

    CharFreq root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
    return root;
}

Queue *createQueue(int capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->capacity = capacity;
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    q->array = (CooldownItem *)malloc(capacity * sizeof(CooldownItem));
    return q;
}

void enqueue(Queue *q, CooldownItem item)
{
    if (q->count == q->capacity) return;
    q->array[q->rear] = item;
    q->rear = (q->rear + 1) % q->capacity;
    q->count++;
}

CooldownItem dequeue(Queue *q)
{
    CooldownItem nullItem;
    nullItem.item.ch = '\0';
    nullItem.item.freq = 0;
    nullItem.releaseTime = -1;

    if (q->count == 0) return nullItem;
    CooldownItem item = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->count--;
    return item;
}

int isQueueEmpty(Queue *q)
{
    return q->count == 0;
}

int validateResult(const char *str, int k)
{
    int n = (int)strlen(str);
    int lastSeen[256];
    for (int i = 0; i < 256; i++)
    {
        lastSeen[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        unsigned char c = (unsigned char)str[i];
        if (lastSeen[c] != -1 && (i - lastSeen[c]) < k)
        {
            return 0;
        }
        lastSeen[c] = i;
    }
    return 1;
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}

void fillStringRandomly(char *str, int n, int alphabetSize)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        str[i] = (char)('a' + randomBtw(0, alphabetSize));
    }
    str[n] = '\0';
}
