#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BIASED_PROBABILITY 0.7

void simulateCoin(int tosses, double probability, int *heads, int *tails)
{
    *heads = 0;
    *tails = 0;

    for (int i = 0; i < tosses; i++)
    {
        double r = rand() / (double)RAND_MAX;

        if (r < probability)
            (*heads)++;
        else
            (*tails)++;
    }
}

int main(void)
{
    srand((unsigned)time(NULL));

    int trials[] = {10, 100, 1000, 10000, 100000};
    int n = sizeof(trials) / sizeof(trials[0]);

    FILE *f = fopen("q2_data.csv", "w");

    if (f == NULL)
    {
        printf("Failed to create CSV file.\n");
        return 1;
    }

    fprintf(f, "Trials,FairHeads,FairTails,FairProbability,BiasedHeads,BiasedTails,BiasedProbability\n");

    printf("==============================================\n");
    printf(" FAIR vs BIASED COIN SIMULATION\n");
    printf("==============================================\n\n");

    for (int i = 0; i < n; i++)
    {
        int fairHeads, fairTails;
        int biasedHeads, biasedTails;

        simulateCoin(trials[i], 0.5, &fairHeads, &fairTails);
        simulateCoin(trials[i], BIASED_PROBABILITY, &biasedHeads, &biasedTails);

        double fairProbability = (double)fairHeads / trials[i];
        double biasedProbability = (double)biasedHeads / trials[i];

        printf("Trials: %d\n", trials[i]);
        printf("----------------------------------------------\n");
        printf("Fair Coin (P(H)=0.5)\n");
        printf("Heads : %d\n", fairHeads);
        printf("Tails : %d\n", fairTails);
        printf("Experimental P(H): %.5f\n\n", fairProbability);

        printf("Biased Coin (P(H)=%.1f)\n", BIASED_PROBABILITY);
        printf("Heads : %d\n", biasedHeads);
        printf("Tails : %d\n", biasedTails);
        printf("Experimental P(H): %.5f\n", biasedProbability);
        printf("==============================================\n\n");

        fprintf(f,
                "%d,%d,%d,%.5f,%d,%d,%.5f\n",
                trials[i],
                fairHeads,
                fairTails,
                fairProbability,
                biasedHeads,
                biasedTails,
                biasedProbability);
    }

    fclose(f);

    printf("Results saved to q2_data.csv\n");
    printf("As the number of tosses increases, the experimental probabilities converge towards the theoretical probabilities (0.5 and %.1f).\n", BIASED_PROBABILITY);

    return 0;
}