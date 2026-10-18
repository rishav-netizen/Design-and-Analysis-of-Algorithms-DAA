#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 32
#define NUM_PEGS 4

long long R[MAX_DISKS + 1];
int opt_k[MAX_DISKS + 1];

int pegs[NUM_PEGS][MAX_DISKS];
int top[NUM_PEGS];
char peg_names[NUM_PEGS] = {'A', 'B', 'C', 'D'};
int move_count = 0;

// Function prototypes
void FrameStewartDP(int max_n);
void InitPegs(int n);
void MoveDisk(int from, int to);
void Hanoi3(int m, int from, int to, int aux);
void Reve(int n, int from, int to, int aux1, int aux2);

int main()
{
    FrameStewartDP(MAX_DISKS);

    int n = 8;
    printf("--- Reve's Puzzle (4 Pegs) ---\n");
    printf("Number of disks: %d\n", n);
    printf("Optimal k: %d\n", opt_k[n]);
    printf("Minimum moves required: %lld\n\n", R[n]);

    InitPegs(n);
    Reve(n, 0, 3, 1, 2);

    printf("\nTotal moves performed: %d\n", move_count);

    printf("\nEnter custom n to solve (or 0 to exit): ");
    if (scanf("%d", &n) == 1 && n > 0 && n <= MAX_DISKS)
    {
        printf("Min moves for %d disks on 4 pegs: %lld (vs %lld for 3 pegs)\n",
               n, R[n], (n < 63 ? (1LL << n) - 1 : -1));
        if (n <= 10)
        {
            InitPegs(n);
            Reve(n, 0, 3, 1, 2);
        }
    }

    return 0;
}

void FrameStewartDP(int max_n)
{
    R[0] = 0;
    opt_k[0] = 0;
    R[1] = 1;
    opt_k[1] = 0;

    for (int n = 2; n <= max_n; n++)
    {
        long long best = -1;
        int best_k = 1;

        for (int k = 1; k < n; k++)
        {
            long long cost = 2LL * R[k] + ((1LL << (n - k)) - 1);
            if (best == -1 || cost < best)
            {
                best = cost;
                best_k = k;
            }
        }
        R[n] = best;
        opt_k[n] = best_k;
    }
}

void InitPegs(int n)
{
    for (int i = 0; i < NUM_PEGS; i++)
    {
        top[i] = -1;
    }
    for (int d = n; d >= 1; d--)
    {
        pegs[0][++top[0]] = d;
    }
    move_count = 0;
}

void MoveDisk(int from, int to)
{
    int disk = pegs[from][top[from]--];
    pegs[to][++top[to]] = disk;
    move_count++;
    printf("Move %2d: Disk %d from %c to %c\n", move_count, disk, peg_names[from], peg_names[to]);
}

void Hanoi3(int m, int from, int to, int aux)
{
    if (m <= 0) return;
    if (m == 1)
    {
        MoveDisk(from, to);
        return;
    }
    Hanoi3(m - 1, from, aux, to);
    MoveDisk(from, to);
    Hanoi3(m - 1, aux, to, from);
}

void Reve(int n, int from, int to, int aux1, int aux2)
{
    if (n <= 0) return;
    if (n == 1)
    {
        MoveDisk(from, to);
        return;
    }

    int k = opt_k[n];
    Reve(k, from, aux1, to, aux2);
    Hanoi3(n - k, from, to, aux2);
    Reve(k, aux1, to, from, aux2);
}
