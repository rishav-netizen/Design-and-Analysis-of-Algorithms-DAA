#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct HTNode {
    int id;
    int isLeaf;
    long long weight;
    int depth;
    struct HTNode *left;
    struct HTNode *right;
} HTNode;

HTNode *createHTLeaf(int id, long long weight);
HTNode *createHTInternal(long long weight, HTNode *left, HTNode *right);
void computeDepths(HTNode *root, int currentDepth);
HTNode *reconstructAlphabeticTree(int n, HTNode **leafNodes, int *depths);
void printTreeInOrder(HTNode *root, int indent);
int randomBtw(int l, int u);
void fillWeightsRandomly(int n, long long *weights, int l, int u);
void displayWeights(int n, long long *weights);

/* Huffman comparison helper */
long long computeHuffmanCost(int n, long long *weights);

int main() {
    int n;
    printf("Enter the number of ordered sequence keys (n >= 2): ");
    scanf("%d", &n);
    while (n < 2)
    {
        printf("Invalid input. n must be at least 2: ");
        scanf("%d", &n);
    }

    long long *weights = (long long *)malloc(n * sizeof(long long));

    int choice;
    printf("Do you wanna: \t(0) Enter weights manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
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
            printf("Enter %d positive weights in strict order: ", n);
            for (int i = 0; i < n; i++)
            {
                scanf("%lld", &weights[i]);
                while (weights[i] <= 0)
                {
                    printf("Weight must be positive. Re-enter key %d: ", i + 1);
                    scanf("%lld", &weights[i]);
                }
            }
            break;
        }

        case 1:
        {
            int l, u;
            printf("Enter lower and upper limits for random weights: ");
            scanf("%d %d", &l, &u);
            while (l <= 0 || l >= u)
            {
                printf("Invalid limits. Re-enter: ");
                scanf("%d %d", &l, &u);
            }
            fillWeightsRandomly(n, weights, l, u);
            break;
        }

        default:
            break;
    }

    printf("\nOrdered sequence weights: ");
    displayWeights(n, weights);

    /* Allocate leaf nodes */
    HTNode **leaves = (HTNode **)malloc(n * sizeof(HTNode *));
    for (int i = 0; i < n; i++)
    {
        leaves[i] = createHTLeaf(i + 1, weights[i]);
    }

    /* Working sequence for Phase 1: Combination Phase */
    int seqLen = n;
    HTNode **seq = (HTNode **)malloc((2 * n) * sizeof(HTNode *));
    for (int i = 0; i < n; i++)
    {
        seq[i] = leaves[i];
    }

    printf("\n================ PHASE 1: COMBINATION PHASE (COMPATIBLE GREEDY) ================\n");
    printf("+-------+------------+------------+-------------------------+-------------------+\n");
    printf("| Merge | Left Node  | Right Node | Compatible Pair Weights | New Parent Weight |\n");
    printf("+-------+------------+------------+-------------------------+-------------------+\n");

    int mergeStep = 1;

    while (seqLen > 1)
    {
        /* Find compatible pair with minimum sum of weights:
           Two nodes seq[i] and seq[j] (i < j) are compatible if there are NO original leaves between them in seq */
        int bestI = -1, bestJ = -1;
        long long minSum = -1;

        for (int i = 0; i < seqLen - 1; i++)
        {
            for (int j = i + 1; j < seqLen; j++)
            {
                /* Check compatibility: all intermediate elements seq[k] (i < k < j) must be internal nodes */
                int compatible = 1;
                for (int k = i + 1; k < j; k++)
                {
                    if (seq[k]->isLeaf)
                    {
                        compatible = 0;
                        break;
                    }
                }

                if (compatible)
                {
                    long long currentSum = seq[i]->weight + seq[j]->weight;
                    if (minSum == -1 || currentSum < minSum)
                    {
                        minSum = currentSum;
                        bestI = i;
                        bestJ = j;
                    }
                }
                else
                {
                    /* Once we hit an original leaf at k, no subsequent j > k can be compatible with i */
                    break;
                }
            }
        }

        /* Create merged internal node */
        HTNode *parent = createHTInternal(minSum, seq[bestI], seq[bestJ]);

        char leftLabel[32], rightLabel[32];
        if (seq[bestI]->isLeaf) snprintf(leftLabel, sizeof(leftLabel), "Leaf %d (%lld)", seq[bestI]->id, seq[bestI]->weight);
        else snprintf(leftLabel, sizeof(leftLabel), "IntNode (%lld)", seq[bestI]->weight);

        if (seq[bestJ]->isLeaf) snprintf(rightLabel, sizeof(rightLabel), "Leaf %d (%lld)", seq[bestJ]->id, seq[bestJ]->weight);
        else snprintf(rightLabel, sizeof(rightLabel), "IntNode (%lld)", seq[bestJ]->weight);

        printf("| %5d | %-10s | %-10s | %lld + %lld = %lld | %17lld |\n",
               mergeStep++, leftLabel, rightLabel, seq[bestI]->weight, seq[bestJ]->weight, minSum, minSum);

        /* Replace seq[bestI] with parent, and delete seq[bestJ] */
        seq[bestI] = parent;
        for (int k = bestJ; k < seqLen - 1; k++)
        {
            seq[k] = seq[k + 1];
        }
        seqLen--;
    }

    HTNode *phase1Root = seq[0];
    printf("+-------+------------+------------+-------------------------+-------------------+\n");

    /* ================ PHASE 2: LEVEL ASSIGNMENT PHASE ================ */
    computeDepths(phase1Root, 0);

    int *depths = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        depths[i] = leaves[i]->depth;
    }

    printf("\n================ PHASE 2: LEVEL ASSIGNMENT RESULTS ================\n");
    printf("+---------+------------+-------------+-------------------+\n");
    printf("| Key (i) | Weight w_i | Level/Depth | Weighted Cost w*d |\n");
    printf("+---------+------------+-------------+-------------------+\n");

    long long totalHuTuckerCost = 0;
    for (int i = 0; i < n; i++)
    {
        long long itemCost = weights[i] * depths[i];
        totalHuTuckerCost += itemCost;
        printf("| Key %-3d | %10lld | %11d | %17lld |\n",
               i + 1, weights[i], depths[i], itemCost);
    }
    printf("+---------+------------+-------------+-------------------+\n");
    printf("Total Optimal Alphabetic Tree Cost : %lld\n", totalHuTuckerCost);

    /* ================ PHASE 3: RECONSTRUCTION PHASE ================ */
    HTNode *alphabeticRoot = reconstructAlphabeticTree(n, leaves, depths);

    printf("\n================ PHASE 3: RECONSTRUCTED ALPHABETIC TREE ================\n");
    printf("Tree Structure (In-Order with hierarchical indentation):\n");
    printTreeInOrder(alphabeticRoot, 0);
    printf("------------------------------------------------------------------------\n");

    /* Comparison with unrestricted Huffman code */
    long long huffmanCost = computeHuffmanCost(n, weights);
    double penalty = (double)(totalHuTuckerCost - huffmanCost) / (double)huffmanCost * 100.0;

    printf("\n================ OPTIMALITY & COMPARISON AUDIT ================\n");
    printf("Unrestricted Huffman Minimum Cost : %lld\n", huffmanCost);
    printf("Alphabetic Hu-Tucker Minimum Cost : %lld\n", totalHuTuckerCost);
    printf("Alphabetic Preservation Overhead   : +%lld (%.2f%% increase over Huffman)\n",
           totalHuTuckerCost - huffmanCost, penalty);
    printf("Order Invariant                    : STRICT IN-ORDER LEAF PRESERVATION MAINTAINED\n");
    printf("================================================================\n");

    free(weights);
    free(leaves);
    free(seq);
    free(depths);
    return 0;
}

HTNode *createHTLeaf(int id, long long weight)
{
    HTNode *node = (HTNode *)malloc(sizeof(HTNode));
    node->id = id;
    node->isLeaf = 1;
    node->weight = weight;
    node->depth = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

HTNode *createHTInternal(long long weight, HTNode *left, HTNode *right)
{
    HTNode *node = (HTNode *)malloc(sizeof(HTNode));
    node->id = -1;
    node->isLeaf = 0;
    node->weight = weight;
    node->depth = 0;
    node->left = left;
    node->right = right;
    return node;
}

void computeDepths(HTNode *root, int currentDepth)
{
    if (!root) return;
    root->depth = currentDepth;
    computeDepths(root->left, currentDepth + 1);
    computeDepths(root->right, currentDepth + 1);
}

HTNode *reconstructAlphabeticTree(int n, HTNode **leafNodes, int *depths)
{
    /* Phase 3: Bottom-up alphabetic reconstruction using depth levels */
    HTNode **currentList = (HTNode **)malloc(n * sizeof(HTNode *));
    int *currentDepths = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        currentList[i] = createHTLeaf(leafNodes[i]->id, leafNodes[i]->weight);
        currentDepths[i] = depths[i];
    }

    int curLen = n;
    while (curLen > 1)
    {
        /* Find maximum depth present */
        int maxD = 0;
        for (int i = 0; i < curLen; i++)
        {
            if (currentDepths[i] > maxD)
            {
                maxD = currentDepths[i];
            }
        }

        /* Find first adjacent pair with depth equal to maxD */
        int pairIdx = -1;
        for (int i = 0; i < curLen - 1; i++)
        {
            if (currentDepths[i] == maxD && currentDepths[i + 1] == maxD)
            {
                pairIdx = i;
                break;
            }
        }

        if (pairIdx == -1)
        {
            /* If no adjacent pair at maxD (e.g., single deep node), reduce its depth */
            for (int i = 0; i < curLen; i++)
            {
                if (currentDepths[i] == maxD)
                {
                    currentDepths[i]--;
                    break;
                }
            }
            continue;
        }

        /* Merge adjacent pair in currentList */
        HTNode *parent = createHTInternal(currentList[pairIdx]->weight + currentList[pairIdx + 1]->weight,
                                          currentList[pairIdx], currentList[pairIdx + 1]);

        currentList[pairIdx] = parent;
        currentDepths[pairIdx] = maxD - 1;

        for (int k = pairIdx + 1; k < curLen - 1; k++)
        {
            currentList[k] = currentList[k + 1];
            currentDepths[k] = currentDepths[k + 1];
        }
        curLen--;
    }

    HTNode *root = currentList[0];
    free(currentList);
    free(currentDepths);
    return root;
}

void printTreeInOrder(HTNode *root, int indent)
{
    if (!root) return;

    printTreeInOrder(root->right, indent + 4);

    for (int i = 0; i < indent; i++) printf(" ");
    if (root->isLeaf)
    {
        printf("[Key %d (w=%lld)]\n", root->id, root->weight);
    }
    else
    {
        printf("(w=%lld)\n", root->weight);
    }

    printTreeInOrder(root->left, indent + 4);
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}

void fillWeightsRandomly(int n, long long *weights, int l, int u)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        weights[i] = randomBtw(l, u);
    }
}

void displayWeights(int n, long long *weights)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%lld", weights[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

/* Simple helper to compute unrestricted Huffman cost for comparison */
long long computeHuffmanCost(int n, long long *weights)
{
    long long *heap = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) heap[i] = weights[i];
    int size = n;

    /* Build heap */
    for (int i = (size - 1) / 2; i >= 0; i--)
    {
        int cur = i;
        while (2 * cur + 1 < size)
        {
            int left = 2 * cur + 1, right = 2 * cur + 2, smallest = cur;
            if (heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            if (smallest != cur)
            {
                long long tmp = heap[cur];
                heap[cur] = heap[smallest];
                heap[smallest] = tmp;
                cur = smallest;
            }
            else break;
        }
    }

    long long cost = 0;
    while (size > 1)
    {
        /* Extract 2 mins */
        long long m1 = heap[0];
        heap[0] = heap[--size];
        int cur = 0;
        while (2 * cur + 1 < size)
        {
            int left = 2 * cur + 1, right = 2 * cur + 2, smallest = cur;
            if (heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            if (smallest != cur)
            {
                long long tmp = heap[cur];
                heap[cur] = heap[smallest];
                heap[smallest] = tmp;
                cur = smallest;
            }
            else break;
        }

        long long m2 = heap[0];
        heap[0] = heap[--size];
        cur = 0;
        while (2 * cur + 1 < size)
        {
            int left = 2 * cur + 1, right = 2 * cur + 2, smallest = cur;
            if (heap[left] < heap[smallest]) smallest = left;
            if (right < size && heap[right] < heap[smallest]) smallest = right;
            if (smallest != cur)
            {
                long long tmp = heap[cur];
                heap[cur] = heap[smallest];
                heap[smallest] = tmp;
                cur = smallest;
            }
            else break;
        }

        long long sum = m1 + m2;
        cost += sum;

        /* Insert sum */
        heap[size] = sum;
        int idx = size++;
        while (idx > 0 && heap[idx] < heap[(idx - 1) / 2])
        {
            long long tmp = heap[idx];
            heap[idx] = heap[(idx - 1) / 2];
            heap[(idx - 1) / 2] = tmp;
            idx = (idx - 1) / 2;
        }
    }

    free(heap);
    return cost;
}
