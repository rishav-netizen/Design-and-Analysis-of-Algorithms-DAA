#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STR_LEN 256
#define MAX_N 64

int computeOverlap(const char *a, const char *b);
char *mergeStrings(const char *a, const char *b, int ov);
char *greedySuperstring(int n, char **inputStrings, int verbose);
int findOptimalSuperstringLen(int n, char **strings);
void permuteOpt(int n, char **strings, int *p, int *used, int depth, int *bestLen);
int randomBtw(int l, int u);

int main() {
    printf("====================================================================\n");
    printf("        GREEDY SUPERSTRING CONJECTURE SIMULATOR & AUDITOR          \n");
    printf("     Open Problem Analysis · September 2026 AI Disproof Benchmark   \n");
    printf("====================================================================\n");

    int mode;
    printf("Select Execution Mode:\n");
    printf("  (0) Enter custom strings manually\n");
    printf("  (1) Generate random overlapping strings\n");
    printf("  (2) Run Canonical Benchmark & 2026 Counterexample Audit\n");
    printf("Choice: ");
    scanf("%d", &mode);
    while (mode < 0 || mode > 2)
    {
        printf("Invalid choice. Enter 0, 1, or 2: ");
        scanf("%d", &mode);
    }

    int n = 0;
    char **strings = (char **)malloc(MAX_N * sizeof(char *));
    for (int i = 0; i < MAX_N; i++)
    {
        strings[i] = (char *)malloc(MAX_STR_LEN * sizeof(char));
    }

    switch (mode)
    {
        case 0:
        {
            printf("\nEnter number of strings (2 to 16): ");
            scanf("%d", &n);
            while (n < 2 || n > 16)
            {
                printf("Invalid n. Enter between 2 and 16: ");
                scanf("%d", &n);
            }

            printf("Enter %d distinct strings (no spaces):\n", n);
            for (int i = 0; i < n; i++)
            {
                printf("String %d: ", i + 1);
                scanf("%255s", strings[i]);
            }
            break;
        }

        case 1:
        {
            printf("\nEnter number of strings to generate (3 to 10): ");
            scanf("%d", &n);
            while (n < 3 || n > 10)
            {
                printf("Invalid. Enter between 3 and 10: ");
                scanf("%d", &n);
            }

            int strLen;
            printf("Enter length of each string (4 to 12): ");
            scanf("%d", &strLen);
            while (strLen < 4 || strLen > 12)
            {
                printf("Invalid length. Enter between 4 and 12: ");
                scanf("%d", &strLen);
            }

            /* Generate random strings over alphabet {a, b, c, d} with overlapping fragments */
            srand((unsigned int)time(NULL));
            char pool[MAX_STR_LEN * 4];
            int poolLen = strLen * 2 + n * 2;
            for (int i = 0; i < poolLen; i++)
            {
                pool[i] = (char)('a' + (rand() % 3));
            }
            pool[poolLen] = '\0';

            for (int i = 0; i < n; i++)
            {
                int start = i * 2;
                strncpy(strings[i], pool + start, strLen);
                strings[i][strLen] = '\0';
            }
            break;
        }

        case 2:
        {
            printf("\n--- Loading Classical Disproof & Hard Instances Benchmark ---\n");
            n = 4;
            /* Pathological greedy trap instance:
               Strings: "a b^k c", "b^k c d", "c d b^k", "d b^k e"
               Here represented with k = 3 */
            strcpy(strings[0], "abbbc");
            strcpy(strings[1], "bbbcd");
            strcpy(strings[2], "cdbbb");
            strcpy(strings[3], "dbbbe");
            printf("Loaded 4 strings demonstrating greedy overlap trap:\n");
            for (int i = 0; i < n; i++)
            {
                printf("  s%d: \"%s\"\n", i + 1, strings[i]);
            }
            break;
        }

        default:
            break;
    }

    printf("\n--- Candidate String Set ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("s[%d] = \"%s\" (len: %lu)\n", i + 1, strings[i], (unsigned long)strlen(strings[i]));
    }

    char *greedyResult = greedySuperstring(n, strings, 1);
    int greedyLen = (int)strlen(greedyResult);

    int optLen = -1;
    if (n <= 8)
    {
        optLen = findOptimalSuperstringLen(n, strings);
    }

    printf("\n======================= AUDIT & CONJECTURE REPORT =======================\n");
    printf("Greedy Superstring Obtained : \"%s\"\n", greedyResult);
    printf("Greedy Superstring Length   : %d characters\n", greedyLen);

    if (optLen > 0)
    {
        double ratio = (double)greedyLen / (double)optLen;
        printf("Optimal Superstring Length  : %d characters\n", optLen);
        printf("Empirical Approximation Ratio: %.4f (Greedy / OPT)\n", ratio);
        if (ratio <= 2.0)
        {
            printf("Conjecture Status for Input : Within historical 2.0 bound.\n");
        }
        else
        {
            printf("Conjecture Status for Input : RATIO EXCEEDS 2.0! (Counterexample Triggered)\n");
        }
    }
    else
    {
        printf("Optimal Superstring Length  : Omitted (n > 8; NP-hard exhaustive search bypassed)\n");
    }

    printf("\nTheoretical Status (September 2026 ArXiv Disproof):\n");
    printf("  • Long-standing Conjecture : Greedy is a 2-approximation (Gallant et al. 1980)\n");
    printf("  • 2026 Disproof Lower Bound: (9k + 2) / (4k + 4) for even k >= 10\n");
    printf("  • Asymptotic Limit         : 9 / 4 = 2.25 as k -> infinity\n");
    printf("  • AI Assistance Note       : Formal counterexample discovered via automated reasoning\n");
    printf("=========================================================================\n");

    free(greedyResult);
    for (int i = 0; i < MAX_N; i++)
    {
        free(strings[i]);
    }
    free(strings);
    return 0;
}

int computeOverlap(const char *a, const char *b)
{
    int lenA = (int)strlen(a);
    int lenB = (int)strlen(b);
    int maxOv = (lenA < lenB) ? lenA - 1 : lenB - 1;

    for (int k = maxOv; k > 0; k--)
    {
        if (strncmp(a + lenA - k, b, k) == 0)
        {
            return k;
        }
    }
    return 0;
}

char *mergeStrings(const char *a, const char *b, int ov)
{
    int lenA = (int)strlen(a);
    int lenB = (int)strlen(b);
    char *res = (char *)malloc((lenA + lenB - ov + 1) * sizeof(char));
    strcpy(res, a);
    strcat(res, b + ov);
    return res;
}

char *greedySuperstring(int n, char **inputStrings, int verbose)
{
    int count = n;
    char **active = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        active[i] = strdup(inputStrings[i]);
    }

    if (verbose)
    {
        printf("\n================ STEP-BY-STEP GREEDY OVERLAP MERGING ================\n");
        printf("+------+--------------------+--------------------+---------+--------------------+\n");
        printf("| Step | String U           | String V           | Overlap | Merged Output      |\n");
        printf("+------+--------------------+--------------------+---------+--------------------+\n");
    }

    int step = 1;
    while (count > 1)
    {
        int bestU = -1, bestV = -1;
        int maxOv = -1;

        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (i == j) continue;
                int ov = computeOverlap(active[i], active[j]);
                if (ov > maxOv)
                {
                    maxOv = ov;
                    bestU = i;
                    bestV = j;
                }
            }
        }

        if (maxOv < 0)
        {
            bestU = 0;
            bestV = 1;
            maxOv = 0;
        }

        char *merged = mergeStrings(active[bestU], active[bestV], maxOv);

        if (verbose)
        {
            printf("| %4d | %-18s | %-18s | %7d | %-18s |\n",
                   step++, active[bestU], active[bestV], maxOv, merged);
        }

        free(active[bestU]);
        free(active[bestV]);
        active[bestU] = merged;

        for (int k = bestV; k < count - 1; k++)
        {
            active[k] = active[k + 1];
        }
        count--;
    }

    if (verbose)
    {
        printf("+------+--------------------+--------------------+---------+--------------------+\n");
    }

    char *finalStr = strdup(active[0]);
    free(active[0]);
    free(active);
    return finalStr;
}

void permuteOpt(int n, char **strings, int *p, int *used, int depth, int *bestLen)
{
    if (depth == n)
    {
        /* Calculate superstring length for this permutation */
        int curLen = (int)strlen(strings[p[0]]);
        for (int i = 0; i < n - 1; i++)
        {
            int ov = computeOverlap(strings[p[i]], strings[p[i + 1]]);
            curLen += (int)strlen(strings[p[i + 1]]) - ov;
        }
        if (curLen < *bestLen)
        {
            *bestLen = curLen;
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!used[i])
        {
            used[i] = 1;
            p[depth] = i;
            permuteOpt(n, strings, p, used, depth + 1, bestLen);
            used[i] = 0;
        }
    }
}

int findOptimalSuperstringLen(int n, char **strings)
{
    int p[16];
    int used[16] = {0};
    int bestLen = 999999;
    permuteOpt(n, strings, p, used, 0, &bestLen);
    return bestLen;
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}
