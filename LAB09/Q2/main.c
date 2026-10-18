#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    int size;
    int capacity;
    Node **array;
} MinHeap;

typedef struct {
    char symbol;
    int freq;
    int length;
    unsigned int canonicalCode;
    char codeStr[64];
} SymbolCode;

Node *createNode(char symbol, int freq);
MinHeap *createMinHeap(int capacity);
void swapNode(Node **a, Node **b);
void minHeapify(MinHeap *heap, int idx);
Node *extractMin(MinHeap *heap);
void insertMinHeap(MinHeap *heap, Node *node);
Node *buildHuffmanTree(char *symbols, int *freqs, int n);
void getCodeLengths(Node *root, int depth, int *lengths, char *symbols, int n);
int compareCanonical(const void *a, const void *b);
void buildCanonicalCodes(SymbolCode *codes, int n);
void displayCodebook(SymbolCode *codes, int n, int totalFreq);
int randomBtw(int l, int u);
void fillFrequenciesRandomly(int n, int *freqs, int l, int u);

int main() {
    int n;
    printf("Enter the number of symbols (2 to 52): ");
    scanf("%d", &n);
    while (n < 2 || n > 52)
    {
        printf("Invalid input. Must be between 2 and 52: ");
        scanf("%d", &n);
    }

    char *symbols = (char *)malloc(n * sizeof(char));
    int *freqs = (int *)malloc(n * sizeof(int));

    int choice;
    printf("Do you wanna: \t(0) Enter symbols and frequencies manually or\n\t\t(1) Have it randomly filled?\nChoice: ");
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
            printf("Enter %d symbol characters and their positive integer frequencies:\n", n);
            for (int i = 0; i < n; i++)
            {
                printf("Symbol %d (Char Freq): ", i + 1);
                scanf(" %c %d", &symbols[i], &freqs[i]);
                while (freqs[i] <= 0)
                {
                    printf("Frequency must be positive. Re-enter Symbol %d (Char Freq): ", i + 1);
                    scanf(" %c %d", &symbols[i], &freqs[i]);
                }
            }
            break;
        }

        case 1:
        {
            int l, u;
            printf("Enter lower and upper limits for random frequencies: ");
            scanf("%d %d", &l, &u);
            while (l <= 0 || l >= u)
            {
                printf("Invalid limits (ensure 0 < l < u). Re-enter: ");
                scanf("%d %d", &l, &u);
            }

            for (int i = 0; i < n; i++)
            {
                if (i < 26)
                {
                    symbols[i] = (char)('A' + i);
                }
                else
                {
                    symbols[i] = (char)('a' + (i - 26));
                }
            }
            fillFrequenciesRandomly(n, freqs, l, u);
            printf("Generated symbols and frequencies:\n");
            for (int i = 0; i < n; i++)
            {
                printf("%c:%d ", symbols[i], freqs[i]);
            }
            printf("\n");
            break;
        }

        default:
            break;
    }

    int totalFreq = 0;
    for (int i = 0; i < n; i++)
    {
        totalFreq += freqs[i];
    }

    Node *root = buildHuffmanTree(symbols, freqs, n);

    int *lengths = (int *)calloc(n, sizeof(int));
    getCodeLengths(root, 0, lengths, symbols, n);

    SymbolCode *codes = (SymbolCode *)malloc(n * sizeof(SymbolCode));
    for (int i = 0; i < n; i++)
    {
        codes[i].symbol = symbols[i];
        codes[i].freq = freqs[i];
        codes[i].length = lengths[i];
        codes[i].canonicalCode = 0;
        codes[i].codeStr[0] = '\0';
    }

    buildCanonicalCodes(codes, n);
    displayCodebook(codes, n, totalFreq);

    free(symbols);
    free(freqs);
    free(lengths);
    free(codes);
    return 0;
}

Node *createNode(char symbol, int freq)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->symbol = symbol;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (Node **)malloc(capacity * sizeof(Node *));
    return heap;
}

void swapNode(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
    {
        smallest = left;
    }

    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        swapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

Node *extractMin(MinHeap *heap)
{
    if (heap->size <= 0) return NULL;
    Node *temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

void insertMinHeap(MinHeap *heap, Node *node)
{
    heap->size++;
    int i = heap->size - 1;
    while (i > 0 && node->freq < heap->array[(i - 1) / 2]->freq)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

Node *buildHuffmanTree(char *symbols, int *freqs, int n)
{
    MinHeap *heap = createMinHeap(n);
    for (int i = 0; i < n; i++)
    {
        heap->array[i] = createNode(symbols[i], freqs[i]);
    }
    heap->size = n;

    for (int i = (heap->size - 1) / 2; i >= 0; i--)
    {
        minHeapify(heap, i);
    }

    while (heap->size > 1)
    {
        Node *left = extractMin(heap);
        Node *right = extractMin(heap);

        Node *top = createNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(heap, top);
    }

    Node *root = extractMin(heap);
    free(heap->array);
    free(heap);
    return root;
}

void getCodeLengths(Node *root, int depth, int *lengths, char *symbols, int n)
{
    if (!root) return;

    if (!root->left && !root->right)
    {
        for (int i = 0; i < n; i++)
        {
            if (symbols[i] == root->symbol)
            {
                lengths[i] = (depth == 0) ? 1 : depth;
                break;
            }
        }
        return;
    }

    getCodeLengths(root->left, depth + 1, lengths, symbols, n);
    getCodeLengths(root->right, depth + 1, lengths, symbols, n);
}

int compareCanonical(const void *a, const void *b)
{
    const SymbolCode *sa = (const SymbolCode *)a;
    const SymbolCode *sb = (const SymbolCode *)b;

    /* Primary: Codeword length ascending */
    if (sa->length != sb->length)
    {
        return sa->length - sb->length;
    }

    /* Secondary: Lexicographical order of symbol */
    return (int)(unsigned char)sa->symbol - (int)(unsigned char)sb->symbol;
}

void buildCanonicalCodes(SymbolCode *codes, int n)
{
    /* Sort symbols by code length ascending, then symbol character */
    qsort(codes, n, sizeof(SymbolCode), compareCanonical);

    unsigned int currentCode = 0;
    int currentLength = codes[0].length;

    for (int i = 0; i < n; i++)
    {
        if (codes[i].length > currentLength)
        {
            currentCode <<= (codes[i].length - currentLength);
            currentLength = codes[i].length;
        }

        codes[i].canonicalCode = currentCode;

        /* Generate binary string */
        for (int b = codes[i].length - 1; b >= 0; b--)
        {
            codes[i].codeStr[codes[i].length - 1 - b] = ((currentCode >> b) & 1) ? '1' : '0';
        }
        codes[i].codeStr[codes[i].length] = '\0';

        currentCode++;
    }
}

void displayCodebook(SymbolCode *codes, int n, int totalFreq)
{
    printf("\n==================== CANONICAL HUFFMAN CODEBOOK ====================\n");
    printf("+--------+-----------+-------------+-------------+-------------------+\n");
    printf("| Symbol | Frequency | Probability | Code Length | Canonical Code    |\n");
    printf("+--------+-----------+-------------+-------------+-------------------+\n");

    double expectedLength = 0.0;
    double entropy = 0.0;
    int totalBits = 0;

    for (int i = 0; i < n; i++)
    {
        double p = (double)codes[i].freq / totalFreq;
        expectedLength += p * codes[i].length;
        entropy -= p * (log(p) / log(2.0));
        totalBits += codes[i].freq * codes[i].length;

        printf("|   '%c'  | %9d | %11.4f | %11d | %-17s |\n",
               codes[i].symbol, codes[i].freq, p, codes[i].length, codes[i].codeStr);
    }
    printf("+--------+-----------+-------------+-------------+-------------------+\n");

    double efficiency = (entropy / expectedLength) * 100.0;
    printf("Total Symbols Processed      : %d\n", n);
    printf("Total Stream Character Count : %d\n", totalFreq);
    printf("Total Encoded Bitstream Size : %d bits (%.2f bytes)\n", totalBits, (double)totalBits / 8.0);
    printf("Entropy (Theoretical Limit)  : %.4f bits/symbol\n", entropy);
    printf("Average Codeword Length (L)  : %.4f bits/symbol\n", expectedLength);
    printf("Coding Efficiency (H / L)    : %.2f%%\n", efficiency);
    printf("Redundancy (L - H)           : %.4f bits/symbol\n", expectedLength - entropy);
    printf("====================================================================\n");
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}

void fillFrequenciesRandomly(int n, int *freqs, int l, int u)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        freqs[i] = randomBtw(l, u);
    }
}
