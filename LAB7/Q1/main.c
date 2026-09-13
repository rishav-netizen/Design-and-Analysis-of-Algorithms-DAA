#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_COINS ((MAX_N * (MAX_N + 1)) / 2)

typedef struct {
    int r;
    int c;
} Point;

typedef struct {
    int id;
    Point pos;
} Coin;

typedef struct {
    int coin_id;
    Point from;
    Point to;
} Move;

// Function prototypes
bool ArePointsEqual(Point p1, Point p2);
int GenerateUpwardTriangle(int n, Coin coins[]);
int FindCoinAt(Point p, const Coin coins[], int total_coins);
int GenerateInvertedTriangle(int n, int row_offset, int col_offset, Point target_pts[]);
int FindOptimalInvertedPlacement(int n, const Coin initial_coins[], int total_coins, Point best_target_pts[]);
int InvertCoinTriangle(int n, Coin coins[], int total_coins, Move moves[]);

int main()
{
    int n;
    printf("Enter triangle size n (e.g. 4): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N)
    {
        printf("Invalid input! Please enter 1 <= n <= %d.\n", MAX_N);
        return 1;
    }

    Coin coins[MAX_COINS];
    int total_coins = GenerateUpwardTriangle(n, coins);

    printf("Total coins: %d\n", total_coins);

    Move moves[MAX_COINS];
    int move_count = InvertCoinTriangle(n, coins, total_coins, moves);

    if (move_count == 0)
    {
        printf("No moves needed.\n");
    }
    else
    {
        printf("Total moves: %d\n", move_count);
        for (int i = 0; i < move_count; i++)
        {
            printf("  Move %d: Slide Coin %2d from (%d, %d) -> (%d, %d)\n",
                   i + 1, moves[i].coin_id,
                   moves[i].from.r, moves[i].from.c,
                   moves[i].to.r, moves[i].to.c);
        }
    }

    int formula = n * (n + 1) / 6;
    printf("\nFormula floor(n*(n+1)/6): %d\n", formula);
    if (move_count == formula)
    {
        printf("Match! Optimal minimum moves achieved.\n");
    }

    return 0;
}

bool ArePointsEqual(Point p1, Point p2)
{
    return (p1.r == p2.r && p1.c == p2.c);
}

int GenerateUpwardTriangle(int n, Coin coins[])
{
    int count = 0;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c <= r; c++)
        {
            coins[count].id = count + 1;
            coins[count].pos.r = r;
            coins[count].pos.c = c;
            count++;
        }
    }
    return count;
}

int FindCoinAt(Point p, const Coin coins[], int total_coins)
{
    for (int i = 0; i < total_coins; i++)
    {
        if (ArePointsEqual(coins[i].pos, p))
        {
            return i;
        }
    }
    return -1;
}

int GenerateInvertedTriangle(int n, int row_offset, int col_offset, Point target_pts[])
{
    int count = 0;
    for (int r = 0; r < n; r++)
    {
        int num_coins_in_row = n - r;
        for (int c = 0; c < num_coins_in_row; c++)
        {
            target_pts[count].r = r + row_offset;
            target_pts[count].c = c + col_offset;
            count++;
        }
    }
    return count;
}

int FindOptimalInvertedPlacement(int n, const Coin initial_coins[], int total_coins, Point best_target_pts[])
{
    int max_overlap = -1;
    Point current_targets[MAX_COINS];

    for (int row_off = 0; row_off <= n; row_off++)
    {
        for (int col_off = -n; col_off <= n; col_off++)
        {
            int count = GenerateInvertedTriangle(n, row_off, col_off, current_targets);
            int overlap = 0;

            for (int i = 0; i < count; i++)
            {
                if (FindCoinAt(current_targets[i], initial_coins, total_coins) != -1)
                {
                    overlap++;
                }
            }

            if (overlap > max_overlap)
            {
                max_overlap = overlap;
                for (int i = 0; i < count; i++)
                {
                    best_target_pts[i] = current_targets[i];
                }
            }
        }
    }
    return max_overlap;
}

int InvertCoinTriangle(int n, Coin coins[], int total_coins, Move moves[])
{
    Point target_pts[MAX_COINS];
    FindOptimalInvertedPlacement(n, coins, total_coins, target_pts);

    bool is_stationary[MAX_COINS] = {false};
    bool is_target_filled[MAX_COINS] = {false};

    for (int i = 0; i < total_coins; i++)
    {
        for (int j = 0; j < total_coins; j++)
        {
            if (ArePointsEqual(coins[i].pos, target_pts[j]))
            {
                is_stationary[i] = true;
                is_target_filled[j] = true;
                break;
            }
        }
    }

    int source_indices[MAX_COINS];
    int num_sources = 0;
    for (int i = 0; i < total_coins; i++)
    {
        if (!is_stationary[i])
        {
            source_indices[num_sources++] = i;
        }
    }

    Point empty_targets[MAX_COINS];
    int num_empty = 0;
    for (int j = 0; j < total_coins; j++)
    {
        if (!is_target_filled[j])
        {
            empty_targets[num_empty++] = target_pts[j];
        }
    }

    for (int i = 0; i < num_sources; i++)
    {
        int coin_idx = source_indices[i];
        moves[i].coin_id = coins[coin_idx].id;
        moves[i].from = coins[coin_idx].pos;
        moves[i].to = empty_targets[i];
        coins[coin_idx].pos = empty_targets[i];
    }

    return num_sources;
}
