#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    double v;          /* Base value */
    double w;          /* Weight */
    double lambda;     /* Decay rate */
    double density;    /* Base density = v / w */
    double fraction;   /* Fraction taken in knapsack [0, 1] */
    double valGained;  /* Effective value contributed */
    double startTime;  /* Scheduled start time */
    double finishTime; /* Scheduled finish time */
} Item;

void fillItemsRandomly(int n, Item *items, double minV, double maxV, double minW, double maxW, double minL, double maxL);
double randomDouble(double min, double max);
int compareItems(const void *a, const void *b);
void displayItems(int n, Item *items);
void displaySchedule(int n, Item *items, double totalVal, double totalWeight, double capacity);

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input try again: ");
        scanf("%d", &n);
    }

    Item *items = (Item *)calloc(n, sizeof(Item));
    for (int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
    }

    int choice;
    printf("Do you wanna: \t(0) Enter item details manually or\n\t\t(1) Have them randomly filled?\nChoice: ");
    scanf("%d", &choice);
    while (choice != 0 && choice != 1)
    {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    switch (choice)
    {
        case 0:
        {
            printf("For each item, enter base value (v), weight (w), and decay rate (lambda):\n");
            for (int i = 0; i < n; i++)
            {
                printf("Item %d (v w lambda): ", i + 1);
                scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda);
                while (items[i].v <= 0 || items[i].w <= 0 || items[i].lambda <= 0)
                {
                    printf("Values must be positive. Re-enter Item %d (v w lambda): ", i + 1);
                    scanf("%lf %lf %lf", &items[i].v, &items[i].w, &items[i].lambda);
                }
                items[i].density = items[i].v / items[i].w;
            }
            break;
        }

        case 1:
        {
            double minV, maxV, minW, maxW, minL, maxL;
            printf("Enter min and max base value: ");
            scanf("%lf %lf", &minV, &maxV);
            while (minV <= 0 || minV >= maxV)
            {
                printf("Invalid bounds. Re-enter min and max base value: ");
                scanf("%lf %lf", &minV, &maxV);
            }

            printf("Enter min and max weight: ");
            scanf("%lf %lf", &minW, &maxW);
            while (minW <= 0 || minW >= maxW)
            {
                printf("Invalid bounds. Re-enter min and max weight: ");
                scanf("%lf %lf", &minW, &maxW);
            }

            printf("Enter min and max decay rate (lambda): ");
            scanf("%lf %lf", &minL, &maxL);
            while (minL <= 0 || minL >= maxL)
            {
                printf("Invalid bounds. Re-enter min and max decay rate: ");
                scanf("%lf %lf", &minL, &maxL);
            }

            fillItemsRandomly(n, items, minV, maxV, minW, maxW, minL, maxL);
            break;
        }

        default:
            break;
    }

    double capacity;
    printf("Enter knapsack capacity (W): ");
    scanf("%lf", &capacity);
    while (capacity <= 0)
    {
        printf("Invalid capacity try again: ");
        scanf("%lf", &capacity);
    }

    printf("\n--- Available Items Before Scheduling ---\n");
    displayItems(n, items);

    /* Sort items by greedy scheduling priority:
       By adjacent pairwise exchange, prioritizing higher decay rate lambda prevents greater deterioration loss.
       Ties are broken by higher base density (v / w). */
    qsort(items, n, sizeof(Item), compareItems);

    double currentTime = 0.0;
    double currentWeight = 0.0;
    double totalValue = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (currentWeight >= capacity)
        {
            items[i].fraction = 0.0;
            items[i].valGained = 0.0;
            items[i].startTime = currentTime;
            items[i].finishTime = currentTime;
            continue;
        }

        double remainingCap = capacity - currentWeight;
        double weightToTake = (items[i].w <= remainingCap) ? items[i].w : remainingCap;
        double frac = weightToTake / items[i].w;

        /* Check if density at current time is still non-negative.
           If density becomes zero during consumption: density(t) = (v/w) - lambda * t = 0 => t_max = density / lambda.
           Effective value = integral from t_start to t_start + weightToTake of (density - lambda * t) dt
                           = weightToTake * (density - lambda * (t_start + weightToTake / 2.0)) */
        double tStart = currentTime;
        double tMax = items[i].density / items[i].lambda;

        if (tStart >= tMax)
        {
            /* Item has decayed completely into negative marginal value; skip taking it */
            items[i].fraction = 0.0;
            items[i].valGained = 0.0;
            items[i].startTime = tStart;
            items[i].finishTime = tStart;
            continue;
        }

        if (tStart + weightToTake > tMax)
        {
            /* Clamp weight taken to point of zero marginal return */
            weightToTake = tMax - tStart;
            frac = weightToTake / items[i].w;
        }

        double tEnd = tStart + weightToTake;
        double avgDensity = items[i].density - items[i].lambda * (tStart + weightToTake / 2.0);
        double valGained = weightToTake * avgDensity;

        if (valGained > 0.0)
        {
            items[i].fraction = frac;
            items[i].valGained = valGained;
            items[i].startTime = tStart;
            items[i].finishTime = tEnd;
            currentTime = tEnd;
            currentWeight += weightToTake;
            totalValue += valGained;
        }
        else
        {
            items[i].fraction = 0.0;
            items[i].valGained = 0.0;
            items[i].startTime = tStart;
            items[i].finishTime = tStart;
        }
    }

    displaySchedule(n, items, totalValue, currentWeight, capacity);

    free(items);
    return 0;
}

void fillItemsRandomly(int n, Item *items, double minV, double maxV, double minW, double maxW, double minL, double maxL)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        items[i].v = randomDouble(minV, maxV);
        items[i].w = randomDouble(minW, maxW);
        items[i].lambda = randomDouble(minL, maxL);
        items[i].density = items[i].v / items[i].w;
    }
}

double randomDouble(double min, double max)
{
    return min + ((double)rand() / (double)RAND_MAX) * (max - min);
}

int compareItems(const void *a, const void *b)
{
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;

    /* Primary key: Decay rate lambda descending (highest decay first to minimize deterioration loss) */
    if (ib->lambda > ia->lambda) return 1;
    if (ib->lambda < ia->lambda) return -1;

    /* Secondary key: Base density v / w descending */
    if (ib->density > ia->density) return 1;
    if (ib->density < ia->density) return -1;

    return 0;
}

void displayItems(int n, Item *items)
{
    printf("+------+------------+------------+---------------+----------------+\n");
    printf("| Item | Base Value |   Weight   | Decay Rate λ  | Density (v/w)  |\n");
    printf("+------+------------+------------+---------------+----------------+\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %4d | %10.2f | %10.2f | %13.4f | %14.4f |\n",
               items[i].id, items[i].v, items[i].w, items[i].lambda, items[i].density);
    }
    printf("+------+------------+------------+---------------+----------------+\n");
}

void displaySchedule(int n, Item *items, double totalVal, double totalWeight, double capacity)
{
    printf("\n======================= OPTIMAL GREEDY SCHEDULE =======================\n");
    printf("+------+----------+-------------+------------+------------+--------------+\n");
    printf("| Item | Fraction | Weight Used | Start Time |  End Time  | Value Gained |\n");
    printf("+------+----------+-------------+------------+------------+--------------+\n");
    for (int i = 0; i < n; i++)
    {
        if (items[i].fraction > 0.0)
        {
            printf("| %4d | %7.2f%% | %11.2f | %10.2f | %10.2f | %12.4f |\n",
                   items[i].id, items[i].fraction * 100.0,
                   items[i].fraction * items[i].w,
                   items[i].startTime, items[i].finishTime, items[i].valGained);
        }
    }
    printf("+------+----------+-------------+------------+------------+--------------+\n");
    printf("Total Knapsack Capacity : %.2f\n", capacity);
    printf("Total Weight Consumed   : %.2f / %.2f\n", totalWeight, capacity);
    printf("Maximum Total Value     : %.4f\n", totalVal);
    printf("========================================================================\n");
}
