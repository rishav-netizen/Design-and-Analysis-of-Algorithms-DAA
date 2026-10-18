#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_EGGS 50
#define MAX_FLOORS 1000

int dp[MAX_EGGS + 1][MAX_FLOORS + 1];
int choice[MAX_EGGS + 1][MAX_FLOORS + 1];

// Function prototypes
void ComputeEggDrop(int max_e, int max_f);
void PrintDropSequence(int floors);

int main()
{
    ComputeEggDrop(MAX_EGGS, MAX_FLOORS);

    int e = 2, f = 100;
    printf("--- Super Egg Testing Experiment ---\n");
    printf("Eggs: %d, Floors: %d\n", e, f);
    printf("Minimum drops required: %d\n", dp[e][f]);
    PrintDropSequence(f);

    printf("\nEnter eggs and floors (e.g. 2 100): ");
    if (scanf("%d %d", &e, &f) == 2 && e > 0 && f > 0)
    {
        if (e > MAX_EGGS) e = MAX_EGGS;
        if (f > MAX_FLOORS) f = MAX_FLOORS;
        printf("Min drops for %d eggs and %d floors: %d\n", e, f, dp[e][f]);
        printf("First floor to drop from: %d\n", choice[e][f]);
    }

    return 0;
}

void ComputeEggDrop(int max_e, int max_f)
{
    for (int e = 1; e <= max_e; e++)
    {
        dp[e][0] = 0;
        dp[e][1] = 1;
        choice[e][0] = 0;
        choice[e][1] = 1;
    }

    for (int f = 1; f <= max_f; f++)
    {
        dp[1][f] = f;
        choice[1][f] = 1;
    }

    for (int e = 2; e <= max_e; e++)
    {
        for (int f = 2; f <= max_f; f++)
        {
            dp[e][f] = INT_MAX;
            int min_diff = INT_MAX;

            for (int k = 1; k <= f; k++)
            {
                int broken = dp[e - 1][k - 1];
                int safe = dp[e][f - k];
                int worst = (broken > safe ? broken : safe) + 1;
                int diff = abs(broken - safe);

                if (worst < dp[e][f] || (worst == dp[e][f] && diff < min_diff))
                {
                    dp[e][f] = worst;
                    choice[e][f] = k;
                    min_diff = diff;
                }
            }
        }
    }
}

void PrintDropSequence(int floors)
{
    printf("Optimal first-egg drop floors: ");
    int curr = 0;
    int remaining = floors;
    int step = choice[2][remaining];

    while (remaining > 0 && step > 0)
    {
        curr += step;
        if (curr > floors) curr = floors;
        printf("%d ", curr);
        if (curr == floors) break;
        remaining = floors - curr;
        step = choice[2][remaining];
    }
    printf("\n");
}
