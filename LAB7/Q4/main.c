#include <stdio.h>
#include <stdlib.h>

#define MAX 32

int switches[MAX + 1];
int n;
int moves = 0;

// Function prototypes
void PrintSwitches();
void Toggle(int k);
void TurnOff(int k);
void TurnOn(int k);

int main()
{
    printf("Enter number of switches: ");
    if (scanf("%d", &n) != 1 || n < 1)
    {
        n = 4;
        printf("Defaulting to n = %d\n", n);
    }

    for (int i = 1; i <= n; i++)
    {
        switches[i] = 1;
    }

    printf("Initial switches: ");
    PrintSwitches();

    TurnOff(n);

    long long formula = (1LL << (n + 1)) / 3;
    printf("\nTotal moves: %d\n", moves);
    printf("Formula floor(2^(n+1)/3): %lld\n", formula);

    return 0;
}

void PrintSwitches()
{
    printf("[");
    for (int i = n; i >= 1; i--)
    {
        printf("%d", switches[i]);
        if (i > 1) printf(" ");
    }
    printf("]\n");
}

void Toggle(int k)
{
    switches[k] ^= 1;
    moves++;
    printf("Move %2d: Toggle switch %d -> ", moves, k);
    PrintSwitches();
}

void TurnOff(int k)
{
    if (k <= 0) return;
    if (k == 1)
    {
        Toggle(1);
        return;
    }
    if (k == 2)
    {
        Toggle(2);
        Toggle(1);
        return;
    }

    TurnOff(k - 2);
    Toggle(k);
    TurnOn(k - 2);
    TurnOff(k - 1);
}

void TurnOn(int k)
{
    if (k <= 0) return;
    if (k == 1)
    {
        Toggle(1);
        return;
    }
    if (k == 2)
    {
        Toggle(1);
        Toggle(2);
        return;
    }

    TurnOn(k - 1);
    TurnOff(k - 2);
    Toggle(k);
    TurnOn(k - 2);
}
