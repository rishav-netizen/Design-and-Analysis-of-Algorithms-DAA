#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Disjoint Set Union structure with Parity (Two-Coloring) */
typedef struct {
    int *parent;
    int *parity; /* parity with respect to parent: 0 = same color, 1 = opposite color */
    int *rank;
    int n;
} BipartiteDSU;

/* Adjacency list representation for accepted edges and cycle tracing */
typedef struct AdjNode {
    int to;
    struct AdjNode *next;
} AdjNode;

typedef struct {
    int numVertices;
    AdjNode **head;
} Graph;

typedef struct {
    int u;
    int v;
} Edge;

/* Function prototypes */
BipartiteDSU *createDSU(int n);
void freeDSU(BipartiteDSU *dsu);
int findSet(BipartiteDSU *dsu, int x, int *p);
bool addEdgeOnline(BipartiteDSU *dsu, int u, int v, bool *isRedundant);

Graph *createGraph(int n);
void addGraphEdge(Graph *g, int u, int v);
void freeGraph(Graph *g);
bool findPathBFS(Graph *g, int src, int dest, int *path, int *pathLen);
void printOddCycle(Graph *g, int u, int v);

int randomBtw(int l, int u);
void fillEdgesRandomly(int m, int v, Edge *edges);
void displayColoring(BipartiteDSU *dsu, int n);

int main() {
    int v;
    printf("Enter number of vertices in graph (V >= 2): ");
    scanf("%d", &v);
    while (v < 2) {
        printf("Invalid input. V must be at least 2: ");
        scanf("%d", &v);
    }

    int m;
    printf("Enter number of edges in online stream (M >= 1): ");
    scanf("%d", &m);
    while (m < 1) {
        printf("Invalid input. M must be at least 1: ");
        scanf("%d", &m);
    }

    Edge *edges = (Edge *)malloc(m * sizeof(Edge));

    int choice;
    printf("Do you wanna: \t(0) Enter edges manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1) {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    switch (choice) {
        case 0: {
            printf("Enter %d edges as pairs (u v) with vertices from 1 to %d:\n", m, v);
            for (int i = 0; i < m; i++) {
                printf("  Edge %d: ", i + 1);
                scanf("%d %d", &edges[i].u, &edges[i].v);
                while (edges[i].u < 1 || edges[i].u > v || edges[i].v < 1 || edges[i].v > v || edges[i].u == edges[i].v) {
                    if (edges[i].u == edges[i].v) {
                        printf("    Self-loops are not allowed in simple bipartite graphs. Re-enter: ");
                    } else {
                        printf("    Vertices must be between 1 and %d. Re-enter: ", v);
                    }
                    scanf("%d %d", &edges[i].u, &edges[i].v);
                }
            }
            break;
        }
        case 1: {
            fillEdgesRandomly(m, v, edges);
            printf("\nRandomly generated edge stream:\n");
            for (int i = 0; i < m; i++) {
                printf("  Edge %d: (%d, %d)\n", i + 1, edges[i].u, edges[i].v);
            }
            break;
        }
        default:
            break;
    }

    BipartiteDSU *dsu = createDSU(v);
    Graph *g = createGraph(v);

    printf("\n======================================================================\n");
    printf("           ONLINE GRAPH BIPARTITENESS TESTING SIMULATION             \n");
    printf("======================================================================\n");

    int acceptedCount = 0;
    int rejectedCount = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i].u - 1; /* 0-based indexing internally */
        int v_node = edges[i].v - 1;

        printf("\n[Step %d] Edge arrives: (%d, %d)\n", i + 1, edges[i].u, edges[i].v);

        bool isRedundant = false;
        bool canAdd = addEdgeOnline(dsu, u, v_node, &isRedundant);

        if (canAdd) {
            if (isRedundant) {
                printf("  -> STATUS: ACCEPTED (Redundant even-cycle cross edge; bipartiteness maintained).\n");
            } else {
                printf("  -> STATUS: ACCEPTED (Connects different components; 2-coloring updated).\n");
                addGraphEdge(g, u, v_node);
            }
            acceptedCount++;
        } else {
            printf("  -> STATUS: REJECTED! Violates bipartiteness!\n");
            printOddCycle(g, u, v_node);
            rejectedCount++;
        }
    }

    printf("\n======================================================================\n");
    printf("                       FINAL VERIFICATION SUMMARY                     \n");
    printf("======================================================================\n");
    printf("Total Edges Processed: %d\n", m);
    printf("Accepted Edges       : %d\n", acceptedCount);
    printf("Rejected (Odd Cycles): %d\n", rejectedCount);
    printf("Final Graph State    : Strictly Bipartite (2-colorable)\n\n");

    displayColoring(dsu, v);

    free(edges);
    freeDSU(dsu);
    freeGraph(g);

    return 0;
}

BipartiteDSU *createDSU(int n) {
    BipartiteDSU *dsu = (BipartiteDSU *)malloc(sizeof(BipartiteDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->parity = (int *)calloc(n, sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->parity[i] = 0;
        dsu->rank[i] = 0;
    }
    return dsu;
}

void freeDSU(BipartiteDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->parity);
        free(dsu->rank);
        free(dsu);
    }
}

int findSet(BipartiteDSU *dsu, int x, int *p) {
    if (dsu->parent[x] == x) {
        *p = 0;
        return x;
    }
    int pParent = dsu->parity[x];
    int rootParity = 0;
    int root = findSet(dsu, dsu->parent[x], &rootParity);
    dsu->parity[x] = pParent ^ rootParity;
    dsu->parent[x] = root;
    *p = dsu->parity[x];
    return root;
}

bool addEdgeOnline(BipartiteDSU *dsu, int u, int v, bool *isRedundant) {
    int pu = 0, pv = 0;
    int ru = findSet(dsu, u, &pu);
    int rv = findSet(dsu, v, &pv);

    *isRedundant = false;

    if (ru == rv) {
        /* In same component: check if colors differ */
        if (pu == pv) {
            /* Path length between u and v is even, so adding edge creates an odd cycle */
            return false;
        }
        /* Path length is odd, adding edge creates an even cycle; bipartiteness safe */
        *isRedundant = true;
        return true;
    }

    /* Merge components with union by rank */
    int requiredParity = pu ^ pv ^ 1;
    if (dsu->rank[ru] < dsu->rank[rv]) {
        dsu->parent[ru] = rv;
        dsu->parity[ru] = requiredParity;
    } else if (dsu->rank[ru] > dsu->rank[rv]) {
        dsu->parent[rv] = ru;
        dsu->parity[rv] = requiredParity;
    } else {
        dsu->parent[ru] = rv;
        dsu->parity[ru] = requiredParity;
        dsu->rank[rv]++;
    }

    return true;
}

Graph *createGraph(int n) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertices = n;
    g->head = (AdjNode **)calloc(n, sizeof(AdjNode *));
    return g;
}

void addGraphEdge(Graph *g, int u, int v) {
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

bool findPathBFS(Graph *g, int src, int dest, int *path, int *pathLen) {
    int n = g->numVertices;
    int *visited = (int *)calloc(n, sizeof(int));
    int *parent = (int *)malloc(n * sizeof(int));
    int *queue = (int *)malloc(n * sizeof(int));
    int head = 0, tail = 0;

    for (int i = 0; i < n; i++) parent[i] = -1;

    visited[src] = 1;
    queue[tail++] = src;

    bool found = false;
    while (head < tail) {
        int u = queue[head++];
        if (u == dest) {
            found = true;
            break;
        }
        for (AdjNode *edge = g->head[u]; edge != NULL; edge = edge->next) {
            int v = edge->to;
            if (!visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                queue[tail++] = v;
            }
        }
    }

    if (found) {
        int curr = dest;
        int len = 0;
        int *temp = (int *)malloc(n * sizeof(int));
        while (curr != -1) {
            temp[len++] = curr;
            curr = parent[curr];
        }
        for (int i = 0; i < len; i++) {
            path[i] = temp[len - 1 - i];
        }
        *pathLen = len;
        free(temp);
    }

    free(visited);
    free(parent);
    free(queue);
    return found;
}

void printOddCycle(Graph *g, int u, int v) {
    int *path = (int *)malloc(g->numVertices * sizeof(int));
    int pathLen = 0;
    if (findPathBFS(g, u, v, path, &pathLen)) {
        printf("  [Odd-Cycle Trace] Length = %d vertices (odd length cycle of %d edges):\n    ", pathLen, pathLen);
        for (int i = 0; i < pathLen; i++) {
            printf("%d -> ", path[i] + 1);
        }
        printf("%d [ODD CYCLE!]\n", path[0] + 1);
    } else {
        printf("  [Odd-Cycle Trace] Vertices %d and %d have identical parity within component.\n", u + 1, v + 1);
    }
    free(path);
}

int randomBtw(int l, int u) {
    return (rand() % (u - l + 1)) + l;
}

void fillEdgesRandomly(int m, int v, Edge *edges) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < m; i++) {
        int u = randomBtw(1, v);
        int w = randomBtw(1, v);
        while (u == w) {
            w = randomBtw(1, v);
        }
        edges[i].u = u;
        edges[i].v = w;
    }
}

void displayColoring(BipartiteDSU *dsu, int n) {
    printf("Bipartite Partitioning of Graph Vertices:\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < n; i++) {
        int parity = 0;
        int root = findSet(dsu, i, &parity);
        char color = (parity == 0) ? 'R' : 'B';
        printf("  Vertex %2d: Color %c (Component Root: %2d, Relative Parity: %d)\n",
               i + 1, color, root + 1, parity);
    }
    printf("\nSet Red (R)  : { ");
    for (int i = 0; i < n; i++) {
        int parity = 0;
        findSet(dsu, i, &parity);
        if (parity == 0) printf("%d ", i + 1);
    }
    printf("}\nSet Blue (B) : { ");
    for (int i = 0; i < n; i++) {
        int parity = 0;
        findSet(dsu, i, &parity);
        if (parity == 1) printf("%d ", i + 1);
    }
    printf("}\n");
}
