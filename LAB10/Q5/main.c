#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int u;
    int v;
} SwapPair;

typedef struct {
    int *parent;
    int *rank;
    int n;
} PermDSU;

/* Function prototypes */
PermDSU *createPermDSU(int n);
void freePermDSU(PermDSU *dsu);
int findSet(PermDSU *dsu, int x);
void unionSets(PermDSU *dsu, int x, int y);

int compareInts(const void *a, const void *b);
void solveLexicographicallySmallest(int n, int *arr, int m, SwapPair *swaps, int *result);

int randomBtw(int l, int u);
void fillDataRandomly(int n, int m, int *arr, SwapPair *swaps);
void displayArray(int n, int *arr);

int main() {
    int n;
    printf("Enter size of permutation array (N >= 1): ");
    scanf("%d", &n);
    while (n < 1) {
        printf("Invalid input. N must be >= 1: ");
        scanf("%d", &n);
    }

    int *arr = (int *)malloc(n * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));

    int m;
    printf("Enter number of allowable swap pairs (M >= 0): ");
    scanf("%d", &m);
    while (m < 0) {
        printf("Invalid input. M must be >= 0: ");
        scanf("%d", &m);
    }

    SwapPair *swaps = (SwapPair *)malloc((m > 0 ? m : 1) * sizeof(SwapPair));

    int choice;
    printf("Do you wanna: \t(0) Enter permutation and swaps manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1) {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    switch (choice) {
        case 0: {
            printf("\nEnter %d elements of permutation A (1 to %d):\n", n, n);
            for (int i = 0; i < n; i++) {
                printf("  A[%d]: ", i + 1);
                scanf("%d", &arr[i]);
            }

            if (m > 0) {
                printf("\nEnter %d allowable swap pairs as 1-based index pairs (u v):\n", m);
                for (int i = 0; i < m; i++) {
                    printf("  Swap %d: ", i + 1);
                    scanf("%d %d", &swaps[i].u, &swaps[i].v);
                    while (swaps[i].u < 1 || swaps[i].u > n || swaps[i].v < 1 || swaps[i].v > n || swaps[i].u == swaps[i].v) {
                        if (swaps[i].u == swaps[i].v) {
                            printf("    Redundant self-swap! Re-enter: ");
                        } else {
                            printf("    Indices must be between 1 and %d. Re-enter: ", n);
                        }
                        scanf("%d %d", &swaps[i].u, &swaps[i].v);
                    }
                }
            }
            break;
        }
        case 1: {
            fillDataRandomly(n, m, arr, swaps);
            printf("\nRandomly Generated Permutation A:\n  ");
            displayArray(n, arr);
            if (m > 0) {
                printf("\nRandomly Generated Allowable Swaps:\n");
                for (int i = 0; i < m; i++) {
                    printf("  Swap %d: (index %d <-> index %d)\n", i + 1, swaps[i].u, swaps[i].v);
                }
            }
            break;
        }
        default:
            break;
    }

    printf("\n======================================================================\n");
    printf("     LEXICOGRAPHICALLY SMALLEST PERMUTATION VIA CONNECTED COMPONENTS   \n");
    printf("======================================================================\n");
    printf("Initial Permutation: ");
    displayArray(n, arr);

    solveLexicographicallySmallest(n, arr, m, swaps, result);

    printf("\n======================================================================\n");
    printf("                          FINAL VERIFICATION                          \n");
    printf("======================================================================\n");
    printf("Original Permutation: ");
    displayArray(n, arr);
    printf("Optimized Result    : ");
    displayArray(n, result);
    printf("\n");

    free(arr);
    free(result);
    free(swaps);

    return 0;
}

PermDSU *createPermDSU(int n) {
    PermDSU *dsu = (PermDSU *)malloc(sizeof(PermDSU));
    dsu->n = n;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

void freePermDSU(PermDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }
}

int findSet(PermDSU *dsu, int x) {
    if (dsu->parent[x] == x) return x;
    return dsu->parent[x] = findSet(dsu, dsu->parent[x]);
}

void unionSets(PermDSU *dsu, int x, int y) {
    int rx = findSet(dsu, x);
    int ry = findSet(dsu, y);
    if (rx == ry) return;

    if (dsu->rank[rx] < dsu->rank[ry]) {
        dsu->parent[rx] = ry;
    } else if (dsu->rank[rx] > dsu->rank[ry]) {
        dsu->parent[ry] = rx;
    } else {
        dsu->parent[rx] = ry;
        dsu->rank[ry]++;
    }
}

int compareInts(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

void solveLexicographicallySmallest(int n, int *arr, int m, SwapPair *swaps, int *result) {
    PermDSU *dsu = createPermDSU(n);

    /* Union all allowable index swap pairs */
    for (int i = 0; i < m; i++) {
        unionSets(dsu, swaps[i].u - 1, swaps[i].v - 1);
    }

    /* Group indices by component root */
    int **compIndices = (int **)malloc(n * sizeof(int *));
    int *compSizes = (int *)calloc(n, sizeof(int));

    /* First pass: count sizes */
    for (int i = 0; i < n; i++) {
        int root = findSet(dsu, i);
        compSizes[root]++;
    }

    /* Allocate memory for each component */
    for (int i = 0; i < n; i++) {
        if (compSizes[i] > 0) {
            compIndices[i] = (int *)malloc(compSizes[i] * sizeof(int));
        } else {
            compIndices[i] = NULL;
        }
    }

    /* Second pass: collect indices in ascending order */
    int *filledCount = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        int root = findSet(dsu, i);
        compIndices[root][filledCount[root]++] = i;
    }

    printf("\nIdentified Connected Index Components:\n");
    printf("---------------------------------------\n");

    /* For each component, extract values, sort in ascending order, and place back */
    for (int r = 0; r < n; r++) {
        if (compSizes[r] > 0) {
            int size = compSizes[r];
            int *values = (int *)malloc(size * sizeof(int));

            printf("Component Representative (Root %d):\n", r + 1);
            printf("  - Index Positions: [ ");
            for (int k = 0; k < size; k++) {
                int idx = compIndices[r][k];
                values[k] = arr[idx];
                printf("%d%s", idx + 1, (k < size - 1) ? ", " : " ");
            }
            printf("]\n  - Initial Values : [ ");
            for (int k = 0; k < size; k++) {
                printf("%d%s", values[k], (k < size - 1) ? ", " : " ");
            }
            printf("]\n");

            /* Sort values in ascending order */
            qsort(values, size, sizeof(int), compareInts);

            printf("  - Sorted Values  : [ ");
            for (int k = 0; k < size; k++) {
                printf("%d%s", values[k], (k < size - 1) ? ", " : " ");
            }
            printf("]\n\n");

            /* Assign sorted values to sorted indices */
            for (int k = 0; k < size; k++) {
                result[compIndices[r][k]] = values[k];
            }

            free(values);
            free(compIndices[r]);
        }
    }

    free(compIndices);
    free(compSizes);
    free(filledCount);
    freePermDSU(dsu);
}

int randomBtw(int l, int u) {
    return (rand() % (u - l + 1)) + l;
}

void fillDataRandomly(int n, int m, int *arr, SwapPair *swaps) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    /* Fisher-Yates shuffle to produce random permutation */
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    for (int i = 0; i < m; i++) {
        int u = randomBtw(1, n);
        int v = randomBtw(1, n);
        while (u == v) {
            v = randomBtw(1, n);
        }
        swaps[i].u = u;
        swaps[i].v = v;
    }
}

void displayArray(int n, int *arr) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : " ");
    }
    printf("]\n");
}
