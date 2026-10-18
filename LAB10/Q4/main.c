#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Graph adjacency list */
typedef struct AdjNode {
    int to;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int numVertices;
    AdjNode **head;
} Graph;

/* Disjoint Set Union with component weight aggregation */
typedef struct {
    int *parent;
    int *rank;
    long long *compWeight;
    int n;
} WeightDSU;

/* Function prototypes */
Graph *createGraph(int n);
void addEdge(Graph *g, int u, int v);
void freeGraph(Graph *g);

WeightDSU *createWeightDSU(int n, long long *weights);
void freeWeightDSU(WeightDSU *dsu);
int findSet(WeightDSU *dsu, int x);
void unionSets(WeightDSU *dsu, int x, int y);

int randomBtw(int l, int u);
void fillDataRandomly(int v, int e, long long *weights, int **edgesArr, int *perm);

int main() {
    int v;
    printf("Enter number of vertices (V >= 1): ");
    scanf("%d", &v);
    while (v < 1) {
        printf("Invalid input. V must be >= 1: ");
        scanf("%d", &v);
    }

    int e;
    printf("Enter number of undirected edges (E >= 0): ");
    scanf("%d", &e);
    while (e < 0) {
        printf("Invalid input. E must be >= 0: ");
        scanf("%d", &e);
    }

    long long *vertexWeights = (long long *)malloc(v * sizeof(long long));
    int **edgesArr = (int **)malloc(e * sizeof(int *));
    for (int i = 0; i < e; i++) {
        edgesArr[i] = (int *)malloc(2 * sizeof(int));
    }
    int *deletionOrder = (int *)malloc(v * sizeof(int));

    int choice;
    printf("Do you wanna: \t(0) Enter graph details manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
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
                scanf("%lld", &vertexWeights[i]);
            }

            if (e > 0) {
                printf("\nEnter %d edges as pairs (u v) with vertices 1 to %d:\n", e, v);
                for (int i = 0; i < e; i++) {
                    printf("  Edge %d: ", i + 1);
                    scanf("%d %d", &edgesArr[i][0], &edgesArr[i][1]);
                    while (edgesArr[i][0] < 1 || edgesArr[i][0] > v || edgesArr[i][1] < 1 || edgesArr[i][1] > v || edgesArr[i][0] == edgesArr[i][1]) {
                        printf("    Invalid edge! No self-loops, vertices 1..%d. Re-enter: ", v);
                        scanf("%d %d", &edgesArr[i][0], &edgesArr[i][1]);
                    }
                }
            }

            printf("\nEnter deletion order of %d vertices (permutation of 1..%d):\n", v, v);
            int *used = (int *)calloc(v + 1, sizeof(int));
            for (int i = 0; i < v; i++) {
                printf("  Deletion %d: ", i + 1);
                scanf("%d", &deletionOrder[i]);
                while (deletionOrder[i] < 1 || deletionOrder[i] > v || used[deletionOrder[i]]) {
                    if (deletionOrder[i] >= 1 && deletionOrder[i] <= v && used[deletionOrder[i]]) {
                        printf("    Vertex %d already in deletion list! Re-enter: ", deletionOrder[i]);
                    } else {
                        printf("    Must be between 1 and %d. Re-enter: ", v);
                    }
                    scanf("%d", &deletionOrder[i]);
                }
                used[deletionOrder[i]] = 1;
            }
            free(used);
            break;
        }
        case 1: {
            fillDataRandomly(v, e, vertexWeights, edgesArr, deletionOrder);
            printf("\nGenerated Vertex Weights:\n  ");
            for (int i = 0; i < v; i++) {
                printf("v%d:%lld ", i + 1, vertexWeights[i]);
                if ((i + 1) % 10 == 0) printf("\n  ");
            }
            printf("\n\nGenerated Edges:\n");
            for (int i = 0; i < e; i++) {
                printf("  Edge %d: (%d, %d)\n", i + 1, edgesArr[i][0], edgesArr[i][1]);
            }
            printf("\nGenerated Deletion Order P = [ ");
            for (int i = 0; i < v; i++) {
                printf("%d%s", deletionOrder[i], (i < v - 1) ? ", " : " ");
            }
            printf("]\n");
            break;
        }
        default:
            break;
    }

    /* Build Adjacency List Graph */
    Graph *g = createGraph(v);
    for (int i = 0; i < e; i++) {
        addEdge(g, edgesArr[i][0] - 1, edgesArr[i][1] - 1);
    }

    printf("\n======================================================================\n");
    printf("        REVERSE TIME-STEP DSU EXECUTION (TIME REVERSAL TRACE)         \n");
    printf("======================================================================\n");

    WeightDSU *dsu = createWeightDSU(v, vertexWeights);
    bool *isActive = (bool *)calloc(v, sizeof(bool));
    long long *maxSumAfterDeletion = (long long *)malloc(v * sizeof(long long));

    long long currentMax = 0;

    /* Process backwards from last deleted vertex down to the first */
    for (int step = v - 1; step >= 0; step--) {
        int u = deletionOrder[step] - 1;
        isActive[u] = true;

        printf("\n[Reverse Step %d] Activating Vertex %d (Weight = %lld)\n",
               v - step, u + 1, vertexWeights[u]);

        if (dsu->compWeight[u] > currentMax) {
            currentMax = dsu->compWeight[u];
        }

        /* Connect to all active neighbors */
        for (AdjNode *curr = g->head[u]; curr != NULL; curr = curr->next) {
            int neighbor = curr->to;
            if (isActive[neighbor]) {
                int rootU = findSet(dsu, u);
                int rootNeighbor = findSet(dsu, neighbor);
                if (rootU != rootNeighbor) {
                    printf("  -> Merging with active neighbor %d (root %d, wt=%lld)\n",
                           neighbor + 1, rootNeighbor + 1, dsu->compWeight[rootNeighbor]);
                    unionSets(dsu, rootU, rootNeighbor);
                    int mergedRoot = findSet(dsu, u);
                    if (dsu->compWeight[mergedRoot] > currentMax) {
                        currentMax = dsu->compWeight[mergedRoot];
                    }
                }
            }
        }

        printf("  => Max Connected Component Sum with vertices {");
        for (int j = step; j < v; j++) {
            printf("%d%s", deletionOrder[j], (j < v - 1) ? ", " : "");
        }
        printf("} active: %lld\n", currentMax);

        /* This state corresponds to the graph AFTER deleting vertices 0..step-1 */
        if (step > 0) {
            maxSumAfterDeletion[step - 1] = currentMax;
        }
    }

    /* After deleting all V vertices, max component sum is 0 */
    maxSumAfterDeletion[v - 1] = 0;

    printf("\n======================================================================\n");
    printf("             FINAL FORWARD DELETION RESULTS (POST-DELETION)           \n");
    printf("======================================================================\n");
    printf("  %-15s | %-16s | %-25s\n", "Step", "Deleted Vertex", "Max Component Weight Remaining");
    printf("  --------------------------------------------------------------------\n");
    for (int i = 0; i < v; i++) {
        printf("  Deletion %-7d | Vertex %-9d | %-25lld\n",
               i + 1, deletionOrder[i], maxSumAfterDeletion[i]);
    }
    printf("  --------------------------------------------------------------------\n\n");

    /* Free allocated resources */
    free(vertexWeights);
    for (int i = 0; i < e; i++) {
        free(edgesArr[i]);
    }
    free(edgesArr);
    free(deletionOrder);
    free(isActive);
    free(maxSumAfterDeletion);
    freeGraph(g);
    freeWeightDSU(dsu);

    return 0;
}

Graph *createGraph(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = n;
    g->head = (AdjNode **)calloc(n, sizeof(AdjNode *));
    return g;
}

void addEdge(Graph *g, int u, int v) {
    AdjNode *node1 = (AdjNode *)malloc(sizeof(AdjNode));
    node1->to = v;
    node1->next = g->head[u];
    g->head[u] = node1;

    AdjNode *node2 = (AdjNode *)malloc(sizeof(AdjNode));
    node2->to = u;
    node2->next = g->head[v];
    g->head[v] = node2;
}

void freeGraph(Graph *g) {
    if (!g) return;
    for (int i = 0; i < g->numVertices; i++) {
        AdjNode *curr = g->head[i];
        while (curr) {
            AdjNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->head);
    free(g);
}

WeightDSU *createWeightDSU(int n, long long *weights) {
    WeightDSU *dsu = (WeightDSU *)malloc(sizeof(WeightDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));
    dsu->compWeight = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
        dsu->compWeight[i] = weights[i];
    }
    return dsu;
}

void freeWeightDSU(WeightDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu->compWeight);
        free(dsu);
    }
}

int findSet(WeightDSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    return dsu->parent[x] = findSet(dsu, dsu->parent[x]);
}

void unionSets(WeightDSU *dsu, int x, int y) {
    int rx = findSet(dsu, x);
    int ry = findSet(dsu, y);
    if (rx == ry) return;

    if (dsu->rank[rx] < dsu->rank[ry]) {
        dsu->parent[rx] = ry;
        dsu->compWeight[ry] += dsu->compWeight[rx];
    } else if (dsu->rank[rx] > dsu->rank[ry]) {
        dsu->parent[ry] = rx;
        dsu->compWeight[rx] += dsu->compWeight[ry];
    } else {
        dsu->parent[rx] = ry;
        dsu->compWeight[ry] += dsu->compWeight[rx];
        dsu->rank[ry]++;
    }
}

int randomBtw(int l, int u) {
    return (rand() % (u - l + 1)) + l;
}

void fillDataRandomly(int v, int e, long long *weights, int **edgesArr, int *perm) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < v; i++) {
        weights[i] = randomBtw(5, 50);
        perm[i] = i + 1;
    }
    /* Fisher-Yates shuffle for random permutation */
    for (int i = v - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = perm[i];
        perm[i] = perm[j];
        perm[j] = temp;
    }

    for (int i = 0; i < e; i++) {
        int u = randomBtw(1, v);
        int w = randomBtw(1, v);
        while (u == w) {
            w = randomBtw(1, v);
        }
        edgesArr[i][0] = u;
        edgesArr[i][1] = w;
    }
}
