#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_SPOTS 100

// Function prototypes
int GenerateStrategy(int n, int shots[]);
void ProveStrategy(int n, int shots[], int total_shots);
void Simulate(int n, int shots[], int total_shots, int start);

int main()
{
    srand(time(NULL));

    int n;
    printf("Enter number of spots: ");
    if (scanf("%d", &n) != 1 || n < 2)
    {
        n = 5;
        printf("Defaulting to n = %d\n", n);
    }

    int shots[2 * MAX_SPOTS];
    int total_shots = GenerateStrategy(n, shots);

    printf("Shooting sequence: ");
    for (int i = 0; i < total_shots; i++)
    {
        printf("%d ", shots[i]);
    }
    printf("\nTotal shots needed: %d\n", total_shots);

    ProveStrategy(n, shots, total_shots);

    int secret = (rand() % n) + 1;
    Simulate(n, shots, total_shots, secret);

    return 0;
}

int GenerateStrategy(int n, int shots[])
{
    if (n <= 1) return 0;
    if (n == 2)
    {
        shots[0] = 2;
        shots[1] = 2;
        return 2;
    }

    int idx = 0;
    for (int i = 2; i <= n - 1; i++)
    {
        shots[idx++] = i;
    }
    for (int i = n - 1; i >= 2; i--)
    {
        shots[idx++] = i;
    }
    return idx;
}

void ProveStrategy(int n, int shots[], int total_shots)
{
    bool possible[MAX_SPOTS + 1];
    for (int i = 1; i <= n; i++)
    {
        possible[i] = true;
    }

    printf("\nBelief state reduction for n = %d:\n", n);

    for (int t = 0; t < total_shots; t++)
    {
        int s = shots[t];
        possible[s] = false;

        bool next[MAX_SPOTS + 1] = {false};
        int remaining = 0;

        for (int i = 1; i <= n; i++)
        {
            if (possible[i])
            {
                if (i > 1) next[i - 1] = true;
                if (i < n) next[i + 1] = true;
            }
        }

        for (int i = 1; i <= n; i++)
        {
            possible[i] = next[i];
            if (possible[i]) remaining++;
        }

        printf("Shot %d at spot %d -> remaining possible spots: %d\n", t + 1, s, remaining);
        if (remaining == 0)
        {
            printf("Target guaranteed hit by shot %d!\n", t + 1);
            return;
        }
    }
}

void Simulate(int n, int shots[], int total_shots, int start)
{
    printf("\nSimulating with target starting at spot %d:\n", start);
    int curr = start;

    for (int t = 0; t < total_shots; t++)
    {
        int shot = shots[t];
        printf("Turn %d: Shooter hits %d, Target is at %d", t + 1, shot, curr);
        if (shot == curr)
        {
            printf(" -> HIT!\n");
            return;
        }

        if (curr == 1) curr = 2;
        else if (curr == n) curr = n - 1;
        else curr = (rand() % 2 == 0) ? curr - 1 : curr + 1;

        printf(" -> Target moved to %d\n", curr);
    }
}
