#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int distance;
    int fuel;
} Station;

typedef struct {
    Station station;
    int key; /* fuel amount used as heap key */
} HeapElement;

typedef struct {
    int size;
    int capacity;
    HeapElement *array;
} MaxHeap;

MaxHeap *createMaxHeap(int capacity);
void swapHeapElement(HeapElement *a, HeapElement *b);
void maxHeapify(MaxHeap *heap, int idx);
void insertMaxHeap(MaxHeap *heap, HeapElement elem);
HeapElement extractMax(MaxHeap *heap);
int compareStations(const void *a, const void *b);
int randomBtw(int l, int u);
void fillStationsRandomly(int n, Station *stations, int targetD, int minFuel, int maxFuel);
void displayStations(int n, Station *stations);

int main() {
    int targetD, startFuel;
    printf("Enter target distance (D): ");
    scanf("%d", &targetD);
    while (targetD <= 0)
    {
        printf("Target distance must be positive. Re-enter D: ");
        scanf("%d", &targetD);
    }

    printf("Enter initial starting fuel (F): ");
    scanf("%d", &startFuel);
    while (startFuel <= 0)
    {
        printf("Initial fuel must be positive. Re-enter F: ");
        scanf("%d", &startFuel);
    }

    int n;
    printf("Enter the number of refueling stations: ");
    scanf("%d", &n);
    while (n < 0)
    {
        printf("Number of stations cannot be negative. Re-enter: ");
        scanf("%d", &n);
    }

    Station *stations = (Station *)malloc((n + 1) * sizeof(Station));

    if (n > 0)
    {
        int choice;
        printf("Do you wanna: \t(0) Enter station details manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
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
                printf("Enter distance from origin (d) and fuel available (f) for each station:\n");
                for (int i = 0; i < n; i++)
                {
                    stations[i].id = i + 1;
                    printf("Station %d (distance fuel): ", i + 1);
                    scanf("%d %d", &stations[i].distance, &stations[i].fuel);
                    while (stations[i].distance <= 0 || stations[i].distance >= targetD || stations[i].fuel <= 0)
                    {
                        printf("Invalid. Ensure 0 < distance < %d and fuel > 0. Re-enter: ", targetD);
                        scanf("%d %d", &stations[i].distance, &stations[i].fuel);
                    }
                }
                break;
            }

            case 1:
            {
                int minFuel, maxFuel;
                printf("Enter min and max fuel capacity for stations: ");
                scanf("%d %d", &minFuel, &maxFuel);
                while (minFuel <= 0 || minFuel >= maxFuel)
                {
                    printf("Invalid fuel range. Re-enter: ");
                    scanf("%d %d", &minFuel, &maxFuel);
                }
                fillStationsRandomly(n, stations, targetD, minFuel, maxFuel);
                break;
            }

            default:
                break;
        }

        /* Sort stations strictly by distance ascending */
        qsort(stations, n, sizeof(Station), compareStations);

        printf("\n--- Sorted Refueling Stations Along Route ---\n");
        displayStations(n, stations);
    }

    /* Treat the target destination D as a dummy terminal station */
    stations[n].id = -1;
    stations[n].distance = targetD;
    stations[n].fuel = 0;

    MaxHeap *heap = createMaxHeap(n + 5);

    int currentFuel = startFuel;
    int currentPos = 0;
    int stopsCount = 0;
    Station *chosenStops = (Station *)malloc((n + 1) * sizeof(Station));
    int possible = 1;

    printf("\n================ VEHICLE JOURNEY SIMULATION ================\n");
    printf("Starting journey from position 0 with Fuel = %d, Target = %d\n", startFuel, targetD);

    for (int i = 0; i <= n; i++)
    {
        int distNeeded = stations[i].distance - currentPos;

        /* If current fuel is insufficient to reach stations[i], greedily consume fuel
           from the best passed stations stored in the Max-Heap (Reverse Greedy) */
        while (currentFuel < distNeeded)
        {
            if (heap->size == 0)
            {
                printf("\n[ERROR] Vehicle ran out of fuel at position %d! Cannot reach distance %d.\n",
                       currentPos + currentFuel, stations[i].distance);
                possible = 0;
                break;
            }

            HeapElement best = extractMax(heap);
            currentFuel += best.station.fuel;
            chosenStops[stopsCount++] = best.station;
            printf("  -> [REFUEL STOP %d] Activated Station %d (at distance %d) adding +%d fuel. Fuel now = %d\n",
                   stopsCount, best.station.id, best.station.distance, best.station.fuel, currentFuel);
        }

        if (!possible)
        {
            break;
        }

        currentFuel -= distNeeded;
        currentPos = stations[i].distance;

        if (i < n)
        {
            HeapElement elem;
            elem.station = stations[i];
            elem.key = stations[i].fuel;
            insertMaxHeap(heap, elem);
        }
    }

    if (possible)
    {
        printf("\n======================= JOURNEY SUMMARY =======================\n");
        printf("Status                   : Successfully reached target destination %d!\n", targetD);
        printf("Minimum Refueling Stops  : %d\n", stopsCount);
        printf("Remaining Fuel at Target : %d\n", currentFuel);
        if (stopsCount > 0)
        {
            printf("\nStops Selected in Optimal Plan:\n");
            printf("+------+------------+---------------+----------------+\n");
            printf("| Stop | Station ID | Distance (km) | Fuel Added (L) |\n");
            printf("+------+------------+---------------+----------------+\n");
            for (int s = 0; s < stopsCount; s++)
            {
                printf("| %4d | %10d | %13d | %14d |\n",
                       s + 1, chosenStops[s].id, chosenStops[s].distance, chosenStops[s].fuel);
            }
            printf("+------+------------+---------------+----------------+\n");
        }
        else
        {
            printf("Initial fuel was sufficient; zero refueling stops required.\n");
        }
        printf("================================================================\n");
    }
    else
    {
        printf("\n======================= JOURNEY SUMMARY =======================\n");
        printf("Status                   : Target UNREACHABLE (-1)\n");
        printf("================================================================\n");
    }

    free(stations);
    free(chosenStops);
    free(heap->array);
    free(heap);

    return 0;
}

MaxHeap *createMaxHeap(int capacity)
{
    MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (HeapElement *)malloc(capacity * sizeof(HeapElement));
    return heap;
}

void swapHeapElement(HeapElement *a, HeapElement *b)
{
    HeapElement temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap *heap, int idx)
{
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].key > heap->array[largest].key)
    {
        largest = left;
    }

    if (right < heap->size && heap->array[right].key > heap->array[largest].key)
    {
        largest = right;
    }

    if (largest != idx)
    {
        swapHeapElement(&heap->array[largest], &heap->array[idx]);
        maxHeapify(heap, largest);
    }
}

void insertMaxHeap(MaxHeap *heap, HeapElement elem)
{
    heap->size++;
    int i = heap->size - 1;
    while (i > 0 && elem.key > heap->array[(i - 1) / 2].key)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = elem;
}

HeapElement extractMax(MaxHeap *heap)
{
    HeapElement nullElem;
    nullElem.station.id = -1;
    nullElem.station.distance = 0;
    nullElem.station.fuel = 0;
    nullElem.key = 0;

    if (heap->size <= 0) return nullElem;
    HeapElement root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
    return root;
}

int compareStations(const void *a, const void *b)
{
    const Station *sa = (const Station *)a;
    const Station *sb = (const Station *)b;
    return sa->distance - sb->distance;
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}

void fillStationsRandomly(int n, Station *stations, int targetD, int minFuel, int maxFuel)
{
    srand((unsigned int)time(NULL));
    int step = targetD / (n + 1);
    if (step < 1) step = 1;

    for (int i = 0; i < n; i++)
    {
        stations[i].id = i + 1;
        int minD = (i * step) + 1;
        int maxD = ((i + 1) * step);
        if (maxD >= targetD) maxD = targetD - 1;
        if (minD >= maxD) minD = maxD - 1;
        if (minD < 1) minD = 1;

        stations[i].distance = (minD < maxD) ? randomBtw(minD, maxD + 1) : minD;
        stations[i].fuel = randomBtw(minFuel, maxFuel + 1);
    }
}

void displayStations(int n, Station *stations)
{
    printf("+------+---------------+----------------+\n");
    printf("|  ID  | Distance (km) | Fuel Stock (L) |\n");
    printf("+------+---------------+----------------+\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %4d | %13d | %14d |\n",
               stations[i].id, stations[i].distance, stations[i].fuel);
    }
    printf("+------+---------------+----------------+\n");
}
