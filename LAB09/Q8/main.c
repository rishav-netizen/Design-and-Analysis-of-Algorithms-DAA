#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int id;
    int start;
    int end;
    int assignedRoom;
} Meeting;

typedef struct {
    int roomId;
    int endTime;
} Room;

typedef struct {
    int size;
    int capacity;
    Room *array;
} MinHeap;

MinHeap *createMinHeap(int capacity);
void swapRoom(Room *a, Room *b);
void minHeapify(MinHeap *heap, int idx);
Room extractMinRoom(MinHeap *heap);
void insertMinHeap(MinHeap *heap, Room r);
int compareMeetings(const void *a, const void *b);
int randomBtw(int l, int u);
void fillMeetingsRandomly(int n, Meeting *meetings, int maxStart, int minDur, int maxDur);
void displayMeetings(int n, Meeting *meetings);

int main() {
    int n;
    printf("Enter the number of meetings: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input try again: ");
        scanf("%d", &n);
    }

    Meeting *meetings = (Meeting *)malloc(n * sizeof(Meeting));

    int choice;
    printf("Do you wanna: \t(0) Enter meeting intervals manually or\n\t\t(1) Have them randomly generated?\nChoice: ");
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
            printf("Enter start and end times for %d meetings:\n", n);
            for (int i = 0; i < n; i++)
            {
                meetings[i].id = i + 1;
                printf("Meeting %d (start end): ", i + 1);
                scanf("%d %d", &meetings[i].start, &meetings[i].end);
                while (meetings[i].start < 0 || meetings[i].end <= meetings[i].start)
                {
                    printf("Invalid interval (ensure 0 <= start < end). Re-enter: ");
                    scanf("%d %d", &meetings[i].start, &meetings[i].end);
                }
                meetings[i].assignedRoom = -1;
            }
            break;
        }

        case 1:
        {
            int maxStart, minDur, maxDur;
            printf("Enter max possible start time: ");
            scanf("%d", &maxStart);
            while (maxStart <= 0)
            {
                printf("Invalid. Re-enter: ");
                scanf("%d", &maxStart);
            }

            printf("Enter min and max meeting duration: ");
            scanf("%d %d", &minDur, &maxDur);
            while (minDur <= 0 || minDur >= maxDur)
            {
                printf("Invalid duration range. Re-enter: ");
                scanf("%d %d", &minDur, &maxDur);
            }

            fillMeetingsRandomly(n, meetings, maxStart, minDur, maxDur);
            break;
        }

        default:
            break;
    }

    printf("\n--- Input Meeting Intervals ---\n");
    displayMeetings(n, meetings);

    /* Sort meetings primarily by start time ascending, secondarily by end time ascending */
    qsort(meetings, n, sizeof(Meeting), compareMeetings);

    MinHeap *heap = createMinHeap(n + 5);
    int totalRoomsCreated = 0;

    printf("\n================ STEP-BY-STEP ROOM ALLOCATION ================\n");
    printf("+-------+------------+----------+----------+-----------------------------+\n");
    printf("| Order | Meeting ID | Interval | Assigned | Action                      |\n");
    printf("+-------+------------+----------+----------+-----------------------------+\n");

    for (int i = 0; i < n; i++)
    {
        if (heap->size > 0 && heap->array[0].endTime <= meetings[i].start)
        {
            /* Earliest room has freed up; reuse it */
            Room freedRoom = extractMinRoom(heap);
            meetings[i].assignedRoom = freedRoom.roomId;

            freedRoom.endTime = meetings[i].end;
            insertMinHeap(heap, freedRoom);

            printf("| %5d | %10d | [%2d, %2d] |  Room %-2d | Reused (Previous ended <= %d) |\n",
                   i + 1, meetings[i].id, meetings[i].start, meetings[i].end,
                   meetings[i].assignedRoom, meetings[i].start);
        }
        else
        {
            /* All active rooms are busy; allocate new room */
            totalRoomsCreated++;
            meetings[i].assignedRoom = totalRoomsCreated;

            Room newRoom;
            newRoom.roomId = totalRoomsCreated;
            newRoom.endTime = meetings[i].end;
            insertMinHeap(heap, newRoom);

            printf("| %5d | %10d | [%2d, %2d] |  Room %-2d | New Room Created            |\n",
                   i + 1, meetings[i].id, meetings[i].start, meetings[i].end,
                   meetings[i].assignedRoom);
        }
    }

    printf("+-------+------------+----------+----------+-----------------------------+\n");

    printf("\n======================= ALLOCATION SUMMARY =======================\n");
    printf("Total Meetings Processed       : %d\n", n);
    printf("Minimum Conference Rooms Needed: %d\n", totalRoomsCreated);
    printf("==================================================================\n");

    printf("\nDetailed Schedule by Conference Room:\n");
    for (int r = 1; r <= totalRoomsCreated; r++)
    {
        printf("  Room %d: ", r);
        int first = 1;
        for (int i = 0; i < n; i++)
        {
            if (meetings[i].assignedRoom == r)
            {
                if (!first) printf(" -> ");
                printf("Meeting %d [%d, %d]", meetings[i].id, meetings[i].start, meetings[i].end);
                first = 0;
            }
        }
        printf("\n");
    }
    printf("==================================================================\n");

    free(meetings);
    free(heap->array);
    free(heap);
    return 0;
}

MinHeap *createMinHeap(int capacity)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (Room *)malloc(capacity * sizeof(Room));
    return heap;
}

void swapRoom(Room *a, Room *b)
{
    Room temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].endTime < heap->array[smallest].endTime)
    {
        smallest = left;
    }

    if (right < heap->size && heap->array[right].endTime < heap->array[smallest].endTime)
    {
        smallest = right;
    }

    if (smallest != idx)
    {
        swapRoom(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

Room extractMinRoom(MinHeap *heap)
{
    Room nullRoom;
    nullRoom.roomId = -1;
    nullRoom.endTime = -1;
    if (heap->size <= 0) return nullRoom;

    Room root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

void insertMinHeap(MinHeap *heap, Room r)
{
    heap->size++;
    int i = heap->size - 1;
    while (i > 0 && r.endTime < heap->array[(i - 1) / 2].endTime)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = r;
}

int compareMeetings(const void *a, const void *b)
{
    const Meeting *ma = (const Meeting *)a;
    const Meeting *mb = (const Meeting *)b;
    if (ma->start != mb->start)
    {
        return ma->start - mb->start;
    }
    return ma->end - mb->end;
}

int randomBtw(int l, int u)
{
    return (rand() % (u - l)) + l;
}

void fillMeetingsRandomly(int n, Meeting *meetings, int maxStart, int minDur, int maxDur)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        meetings[i].id = i + 1;
        meetings[i].start = randomBtw(0, maxStart);
        int dur = randomBtw(minDur, maxDur + 1);
        meetings[i].end = meetings[i].start + dur;
        meetings[i].assignedRoom = -1;
    }
}

void displayMeetings(int n, Meeting *meetings)
{
    printf("+------------+------------+----------+\n");
    printf("| Meeting ID | Start Time | End Time |\n");
    printf("+------------+------------+----------+\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %10d | %10d | %8d |\n",
               meetings[i].id, meetings[i].start, meetings[i].end);
    }
    printf("+------------+------------+----------+\n");
}
