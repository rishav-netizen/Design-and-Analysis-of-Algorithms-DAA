#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int r;
    int c;
} Position;

typedef struct {
    int *parent;
    int *rank;
    int numElements;
} GridDSU;

/* Function prototypes */
GridDSU *createGridDSU(int n);
void freeGridDSU(GridDSU *dsu);
int findSet(GridDSU *dsu, int x);
bool unionSets(GridDSU *dsu, int x, int y);

int randomBtw(int l, int u);
void fillPositionsRandomly(int k, int r, int c, Position *positions);
void printGrid(int **grid, int r, int c);

int main() {
    int rows, cols;
    printf("Enter grid dimensions (Rows and Columns, >= 1): ");
    scanf("%d %d", &rows, &cols);
    while (rows < 1 || cols < 1) {
        printf("Invalid dimensions. Must be >= 1. Re-enter (Rows Columns): ");
        scanf("%d %d", &rows, &cols);
    }

    int k;
    printf("Enter number of land additions (k >= 1): ");
    scanf("%d", &k);
    while (k < 1) {
        printf("Invalid input. k must be >= 1. Re-enter k: ");
        scanf("%d", &k);
    }

    Position *positions = (Position *)malloc(k * sizeof(Position));

    int choice;
    printf("Do you wanna: \t(0) Enter land positions manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1) {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    switch (choice) {
        case 0: {
            printf("Enter %d land positions as (r c) with 1-based indexing (1..%d, 1..%d):\n", k, rows, cols);
            for (int i = 0; i < k; i++) {
                printf("  Position %d: ", i + 1);
                scanf("%d %d", &positions[i].r, &positions[i].c);
                while (positions[i].r < 1 || positions[i].r > rows || positions[i].c < 1 || positions[i].c > cols) {
                    printf("    Out of grid bounds! Must be within 1..%d and 1..%d: ", rows, cols);
                    scanf("%d %d", &positions[i].r, &positions[i].c);
                }
            }
            break;
        }
        case 1: {
            fillPositionsRandomly(k, rows, cols, positions);
            printf("\nRandomly generated land positions:\n");
            for (int i = 0; i < k; i++) {
                printf("  Step %d: (%d, %d)\n", i + 1, positions[i].r, positions[i].c);
            }
            break;
        }
        default:
            break;
    }

    /* Initialize 2D grid: 0 = water, 1 = land */
    int **grid = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int *)calloc(cols, sizeof(int));
    }

    int totalCells = rows * cols;
    GridDSU *dsu = createGridDSU(totalCells);

    printf("\n======================================================================\n");
    printf("             DYNAMIC GRID CONNECTED COMPONENTS (NUMBER OF ISLANDS II) \n");
    printf("======================================================================\n");
    printf("Initial State: %d x %d Grid completely submerged in water (0 Islands).\n", rows, cols);

    int islandCount = 0;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    int *answers = (int *)malloc(k * sizeof(int));

    for (int step = 0; step < k; step++) {
        int r = positions[step].r - 1; /* convert to 0-based indexing */
        int c = positions[step].c - 1;
        int currId = r * cols + c;

        printf("\n----------------------------------------------------------------------\n");
        printf("[Step %d] Add Land at Position (%d, %d)\n", step + 1, r + 1, c + 1);

        if (grid[r][c] == 1) {
            printf("  -> Cell is already land! No new island or merge occurs.\n");
            printf("  -> Current Number of Islands: %d\n", islandCount);
            answers[step] = islandCount;
            continue;
        }

        /* Mark cell as land */
        grid[r][c] = 1;
        dsu->parent[currId] = currId;
        dsu->rank[currId] = 0;
        islandCount++;

        printf("  -> New land created. Initial island count incremented to %d.\n", islandCount);

        /* Inspect 4-directional cardinal neighbors */
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (grid[nr][nc] == 1) {
                    int neighborId = nr * cols + nc;
                    int rootCurr = findSet(dsu, currId);
                    int rootNeighbor = findSet(dsu, neighborId);

                    if (rootCurr != rootNeighbor) {
                        unionSets(dsu, rootCurr, rootNeighbor);
                        islandCount--;
                        printf("     Adjacent land at (%d, %d) merged! Islands decrement to %d.\n",
                               nr + 1, nc + 1, islandCount);
                    }
                }
            }
        }

        answers[step] = islandCount;
        printf("  => Island count after step %d: %d\n", step + 1, islandCount);

        if (rows <= 12 && cols <= 20) {
            printGrid(grid, rows, cols);
        }
    }

    printf("\n======================================================================\n");
    printf("                          SIMULATION SUMMARY                          \n");
    printf("======================================================================\n");
    printf("Sequence of Island Counts: [ ");
    for (int i = 0; i < k; i++) {
        printf("%d%s", answers[i], (i < k - 1) ? ", " : " ");
    }
    printf("]\nFinal Island Count       : %d\n\n", islandCount);

    /* Clean up allocated memory */
    free(answers);
    free(positions);
    freeGridDSU(dsu);
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}

GridDSU *createGridDSU(int n) {
    GridDSU *dsu = (GridDSU *)malloc(sizeof(GridDSU));
    dsu->numElements = n;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = -1; /* Unassigned until activated as land */
        dsu->rank[i] = 0;
    }
    return dsu;
}

void freeGridDSU(GridDSU *dsu) {
    if (dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }
}

int findSet(GridDSU *dsu, int x) {
    if (dsu->parent[x] == x) {
        return x;
    }
    return dsu->parent[x] = findSet(dsu, dsu->parent[x]);
}

bool unionSets(GridDSU *dsu, int x, int y) {
    int rx = findSet(dsu, x);
    int ry = findSet(dsu, y);
    if (rx == ry) return false;

    if (dsu->rank[rx] < dsu->rank[ry]) {
        dsu->parent[rx] = ry;
    } else if (dsu->rank[rx] > dsu->rank[ry]) {
        dsu->parent[ry] = rx;
    } else {
        dsu->parent[rx] = ry;
        dsu->rank[ry]++;
    }
    return true;
}

int randomBtw(int l, int u) {
    return (rand() % (u - l + 1)) + l;
}

void fillPositionsRandomly(int k, int r, int c, Position *positions) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < k; i++) {
        positions[i].r = randomBtw(1, r);
        positions[i].c = randomBtw(1, c);
    }
}

void printGrid(int **grid, int r, int c) {
    printf("     Grid Visualization:\n     ");
    for (int j = 0; j < c; j++) printf("%2d ", j + 1);
    printf("\n     +");
    for (int j = 0; j < c; j++) printf("---");
    printf("+\n");

    for (int i = 0; i < r; i++) {
        printf("  %2d |", i + 1);
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 1) {
                printf(" # ");
            } else {
                printf(" . ");
            }
        }
        printf("|\n");
    }
    printf("     +");
    for (int j = 0; j < c; j++) printf("---");
    printf("+\n");
}
