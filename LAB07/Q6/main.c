#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_SCIENTISTS 100

typedef struct {
    char name[MAX_NAME];
    int birth;
    int death;
} Scientist;

typedef struct {
    int year;
    int type; // -1 for death, +1 for birth
    int id;
} Event;

// Function prototypes
int CompareEvents(const void *a, const void *b);
void FindBestTime(Scientist *scientists, int n);

int main()
{
    Scientist sample[] = {
        {"Galileo Galilei", 1564, 1642},
        {"Isaac Newton", 1643, 1727},
        {"Johannes Kepler", 1571, 1630},
        {"Rene Descartes", 1596, 1650},
        {"Blaise Pascal", 1623, 1662},
        {"Robert Boyle", 1627, 1691},
        {"Robert Hooke", 1635, 1703},
        {"Gottfried Leibniz", 1646, 1716},
        {"Leonhard Euler", 1707, 1783},
        {"Carl Friedrich Gauss", 1777, 1855},
        {"James Clerk Maxwell", 1831, 1879},
        {"Charles Darwin", 1809, 1882},
        {"Albert Einstein", 1879, 1955},
        {"Niels Bohr", 1885, 1962},
        {"Max Planck", 1858, 1947}
    };

    int n = sizeof(sample) / sizeof(sample[0]);

    printf("Index of prominent scientists in database:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%2d. %-22s [%d - %d]\n", i + 1, sample[i].name, sample[i].birth, sample[i].death);
    }

    FindBestTime(sample, n);

    printf("\nDo you want to enter custom scientists? (1 for Yes, 0 for No): ");
    int choice;
    if (scanf("%d", &choice) == 1 && choice == 1)
    {
        int custom_n;
        printf("Enter number of scientists: ");
        if (scanf("%d", &custom_n) == 1 && custom_n > 0)
        {
            Scientist *custom = malloc(custom_n * sizeof(Scientist));
            for (int i = 0; i < custom_n; i++)
            {
                printf("Scientist %d (Name Birth Death): ", i + 1);
                scanf("%s %d %d", custom[i].name, &custom[i].birth, &custom[i].death);
            }
            FindBestTime(custom, custom_n);
            free(custom);
        }
    }

    return 0;
}

int CompareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    // Death happens before birth if in same year
    return e1->type - e2->type;
}

void FindBestTime(Scientist *scientists, int n)
{
    Event events[2 * MAX_SCIENTISTS];
    int event_count = 0;

    for (int i = 0; i < n; i++)
    {
        events[event_count].year = scientists[i].birth;
        events[event_count].type = 1;
        events[event_count].id = i;
        event_count++;

        events[event_count].year = scientists[i].death;
        events[event_count].type = -1;
        events[event_count].id = i;
        event_count++;
    }

    qsort(events, event_count, sizeof(Event), CompareEvents);

    int curr_alive = 0;
    int max_alive = 0;
    int best_year = 0;

    for (int i = 0; i < event_count; i++)
    {
        curr_alive += events[i].type;
        if (curr_alive > max_alive)
        {
            max_alive = curr_alive;
            best_year = events[i].year;
        }
    }

    printf("\n--- Results ---\n");
    printf("Peak year: %d\n", best_year);
    printf("Maximum prominent scientists alive simultaneously: %d\n", max_alive);
    printf("Scientists alive in %d:\n", best_year);

    for (int i = 0; i < n; i++)
    {
        if (scientists[i].birth <= best_year && scientists[i].death > best_year)
        {
            printf("  - %s (%d - %d)\n", scientists[i].name, scientists[i].birth, scientists[i].death);
        }
    }
}
