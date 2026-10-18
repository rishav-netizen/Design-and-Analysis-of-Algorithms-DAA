#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <limits.h>

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

typedef struct {
    int rootId;
    int version;
    long long totalWeight;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MaxHeap;

typedef struct {
    int *parent;
    int *rank;
    int *compSize;
    long long *compWeight;
    int *version;
    int n;
} ConstrainedDSU;

/* Function prototypes */
ConstrainedDSU *createConstrainedDSU(int n, int *vertexWeights);
void freeConstrainedDSU(ConstrainedDSU *dsu);
int findSet(ConstrainedDSU *dsu, int x);
bool unionComponents(ConstrainedDSU *dsu, int u, int v, MaxHeap *heap, int kThreshold, int *validCount);

MaxHeap *createMaxHeap(int capacity);
void freeMaxHeap(MaxHeap *heap);
void insertMaxHeap(MaxHeap *heap, HeapNode node);
void maxHeapify(MaxHeap *heap, int idx);
bool getMaxValidWeight(MaxHeap *heap, ConstrainedDSU *dsu, int kThreshold, long long *maxVal, int *bestRoot);

int randomBtw(int l, int u);
void fillDataRandomly(int v, int m, int *vertexWeights, Edge *edges, int maxW);
void displayAllComponents(ConstrainedDSU *dsu, int n, int kThreshold);

int main() {
    int v;
    printf("Enter number of vertices (V >= 1): ");
    scanf("%d", &v);
    while (v < 1) {
        printf("Invalid input. V must be >= 1: ");
        scanf("%d", &v);
    }

    int kThreshold;
    printf("Enter component size threshold (K >= 1): ");
    scanf("%d", &kThreshold);
    while (kThreshold < 1) {
        printf("Invalid input. K must be >= 1: ");
        scanf("%d", &kThreshold);
    }

    int m;
    printf("Enter number of edges to add sequentially (M >= 1): ");
    scanf("%d", &m);
    while (m < 1) {
        printf("Invalid input. M must be >= 1: ");
        scanf("%d", &m);
    }

    int *vertexWeights = (int *)malloc(v * sizeof(int));
    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    int choice;
    printf("Do you wanna: \t(0) Enter weights and edges manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1) {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    switch (choice) {
        case 0: {
            printf("\nEnter vertex weights for %d vertices (1 to %d):\n", v, v);
            for (int i = 0; i < v; i++) {
                printf("  Vertex %d weight: ", i + 1);
                scanf("%d", &vertexWeights[i]);
            }

            printf("\nEnter %d edges as (u v edge_weight) with vertices 1 to %d:\n", m, v);
            for (int i = 0; i < m; i++) {
                printf("  Edge %d: ", i + 1);
                scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
                while (edges[i].u < 1 || edges[i].u > v || edges[i].v < 1 || edges[i].v > v || edges[i].u == edges[i].v) {
                    if (edges[i].u == edges[i].v) {
                        printf("    Self-loops not allowed. Re-enter: ");
                    } else {
                        printf("    Vertices must be between 1 and %d. Re-enter: ", v);
                    }
                    scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
                }
            }
            break;
        }
        case 1: {
            fillDataRandomly(v, m, vertexWeights, edges, 100);
            printf("\nGenerated Vertex Weights:\n  ");
            for (int i = 0; i < v; i++) {
                printf("v%d:%d ", i + 1, vertexWeights[i]);
                if ((i + 1) % 10 == 0) printf("\n  ");
            }
            printf("\n\nGenerated Sequential Edges:\n");
            for (int i = 0; i < m; i++) {
                printf("  Edge %d: (%d, %d) with weight %d\n", i + 1, edges[i].u, edges[i].v, edges[i].weight);
            }
            break;
        }
        default:
            break;
    }

    ConstrainedDSU *dsu = createConstrainedDSU(v, vertexWeights);
    MaxHeap *heap = createMaxHeap(v + 2 * m + 10);

    int validCount = 0;
    /* Initially every single vertex is a component of size 1 */
    for (int i = 0; i < v; i++) {
        if (1 <= kThreshold) {
            HeapNode node = {i, dsu->version[i], dsu->compWeight[i]};
            insertMaxHeap(heap, node);
            validCount++;
        }
    }

    printf("\n======================================================================\n");
    printf("       MAXIMUM WEIGHT COMPONENT WITH SIZE CONSTRAINT (SIZE <= %d)     \n", kThreshold);
    printf("======================================================================\n");

    long long initMaxVal = 0;
    int initBestRoot = -1;
    if (getMaxValidWeight(heap, dsu, kThreshold, &initMaxVal, &initBestRoot)) {
        printf("Initial State (0 edges): Max Weight = %lld (Component Root: %d, Size: %d)\n",
               initMaxVal, initBestRoot + 1, dsu->compSize[initBestRoot]);
    } else {
        printf("Initial State (0 edges): No component satisfies size <= %d.\n", kThreshold);
    }

    for (int step = 0; step < m; step++) {
        int u = edges[step].u - 1;
        int w = edges[step].v - 1;
        int ew = edges[step].weight;

        printf("\n----------------------------------------------------------------------\n");
        printf("[Step %d] Edge arrives: (%d, %d) [Edge Weight = %d]\n",
               step + 1, edges[step].u, edges[step].v, ew);

        int ru = findSet(dsu, u);
        int rv = findSet(dsu, w);

        if (ru == rv) {
            printf("  -> Redundant edge: vertices %d and %d are already in component %d.\n",
                   u + 1, w + 1, ru + 1);
        } else {
            printf("  -> Merging component %d (size=%d, wt=%lld) with component %d (size=%d, wt=%lld)\n",
                   ru + 1, dsu->compSize[ru], dsu->compWeight[ru],
                   rv + 1, dsu->compSize[rv], dsu->compWeight[rv]);
            unionComponents(dsu, u, w, heap, kThreshold, &validCount);
        }

        long long currentMaxWeight = 0;
        int bestRoot = -1;
        bool exists = getMaxValidWeight(heap, dsu, kThreshold, &currentMaxWeight, &bestRoot);

        if (exists) {
            printf("  => MAX COMPONENT WEIGHT (Size <= %d): %lld (at Component Root %d, Size = %d)\n",
                   kThreshold, currentMaxWeight, bestRoot + 1, dsu->compSize[bestRoot]);
        } else {
            printf("  => MAX COMPONENT WEIGHT (Size <= %d): NONE (all components exceed size %d)\n",
                   kThreshold, kThreshold);
        }
    }

    printf("\n======================================================================\n");
    printf("                      FINAL GRAPH COMPONENT STATUS                    \n");
    printf("======================================================================\n");
    displayAllComponents(dsu, v, kThreshold);

    free(vertexWeights);
    free(edges);
    freeConstrainedDSU(dsu);
    freeMaxHeap(heap);

    return 0;
}

ConstrainedDSU *createConstrainedDSU(int n, int *vertexWeights) {
    ConstrainedDSU *dsu = (ConstrainedDSU *)malloc(sizeof(ConstrainedDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));
    dsu->compSize = (int *)malloc(n * sizeof(int));
    dsu->compWeight = (long long *)malloc(n * sizeof(long long));
    dsu->version = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
        dsu->compSize[i] = 1;
        dsu->compWeight[i] = vertexWeights[i];
        dsu->version[i] = 1;
    }
    return dsu;
}

void freeConstrainedDSU(ConstrainedDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu->compSize);
        free(dsu->compWeight);
        free(dsu->version);
        free(dsu);
    }
}

int findSet(ConstrainedDSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    return dsu->parent[x] = findSet(dsu, dsu->parent[x]);
}

bool unionComponents(ConstrainedDSU *dsu, int u, int v, MaxHeap *heap, int kThreshold, int *validCount) {
    int ru = findSet(dsu, u);
    int rv = findSet(dsu, v);
    if (ru == rv) return false;

    if (dsu->compSize[ru] <= kThreshold) (*validCount)--;
    if (dsu->compSize[rv] <= kThreshold) (*validCount)--;

    int newRoot = ru;
    int childRoot = rv;
    if (dsu->rank[ru] < dsu->rank[rv]) {
        newRoot = rv;
        childRoot = ru;
    } else if (dsu->rank[ru] == dsu->rank[rv]) {
        dsu->rank[ru]++;
    }

    dsu->parent[childRoot] = newRoot;
    dsu->compSize[newRoot] += dsu->compSize[childRoot];
    dsu->compWeight[newRoot] += dsu->compWeight[childRoot];
    dsu->version[newRoot]++;
    dsu->version[childRoot]++;

    if (dsu->compSize[newRoot] <= kThreshold) {
        (*validCount)++;
        HeapNode node = {newRoot, dsu->version[newRoot], dsu->compWeight[newRoot]};
        insertMaxHeap(heap, node);
        printf("     Merged component root %d has size %d <= %d (weight=%lld) -> ELIGIBLE\n",
               newRoot + 1, dsu->compSize[newRoot], kThreshold, dsu->compWeight[newRoot]);
    } else {
        printf("     Merged component root %d has size %d > %d -> EXCEEDS THRESHOLD (ineligible)\n",
               newRoot + 1, dsu->compSize[newRoot], kThreshold);
    }

    return true;
}

MaxHeap *createMaxHeap(int capacity) {
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    return heap;
}

void freeMaxHeap(MaxHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void insertMaxHeap(MaxHeap *heap, HeapNode node) {
    if (heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = (HeapNode *)realloc(heap->data, heap->capacity * sizeof(HeapNode));
    }
    int i = heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].totalWeight < node.totalWeight) {
            heap->data[i] = heap->data[parent];
            i = parent;
        } else {
            break;
        }
    }
    heap->data[i] = node;
}

void maxHeapify(MaxHeap *heap, int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].totalWeight > heap->data[largest].totalWeight) {
        largest = left;
    }
    if (right < heap->size && heap->data[right].totalWeight > heap->data[largest].totalWeight) {
        largest = right;
    }
    if (largest != idx) {
        HeapNode temp = heap->data[idx];
        heap->data[idx] = heap->data[largest];
        heap->data[largest] = temp;
        maxHeapify(heap, largest);
    }
}

bool getMaxValidWeight(MaxHeap *heap, ConstrainedDSU *dsu, int kThreshold, long long *maxVal, int *bestRoot) {
    while (heap->size > 0) {
        HeapNode top = heap->data[0];
        int r = top.rootId;

        /* Check if root is still representative and version matches and size <= K */
        if (dsu->parent[r] == r && dsu->version[r] == top.version && dsu->compSize[r] <= kThreshold) {
            *maxVal = top.totalWeight;
            *bestRoot = r;
            return true;
        }

        /* Discard stale or invalidated heap entry */
        heap->data[0] = heap->data[--heap->size];
        if (heap->size > 0) {
            maxHeapify(heap, 0);
        }
    }
    return false;
}

int randomBtw(int l, int u) {
    return (rand() % (u - l + 1)) + l;
}

void fillDataRandomly(int v, int m, int *vertexWeights, Edge *edges, int maxW) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < v; i++) {
        vertexWeights[i] = randomBtw(5, maxW);
    }
    for (int i = 0; i < m; i++) {
        int u = randomBtw(1, v);
        int w = randomBtw(1, v);
        while (u == w) {
            w = randomBtw(1, v);
        }
        edges[i].u = u;
        edges[i].v = w;
        edges[i].weight = randomBtw(1, 50);
    }
}

void displayAllComponents(ConstrainedDSU *dsu, int n, int kThreshold) {
    int *visited = (int *)calloc(n, sizeof(int));
    printf("Component Breakdown:\n");
    for (int i = 0; i < n; i++) {
        int r = findSet(dsu, i);
        if (!visited[r]) {
            visited[r] = 1;
            printf("  Component Root %2d: Size = %2d, Total Vertex Weight = %5lld | %s\n",
                   r + 1, dsu->compSize[r], dsu->compWeight[r],
                   (dsu->compSize[r] <= kThreshold) ? "ELIGIBLE (<= K)" : "EXCEEDS K");
        }
    }
    free(visited);
}
