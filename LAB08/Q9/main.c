#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#define INITIAL_CAPACITY 64

// Encapsulates the complete trajectory details for a given starting integer
typedef struct
{
    uint64_t start_n;
    uint64_t peak_val;
    size_t steps;
    uint64_t *path;     // Dynamically allocated array of trajectory points
    size_t capacity;
    int overflow_occurred;
} Trajectory;

// Computes next Collatz value with overflow prevention
uint64_t getNextCollatz(uint64_t n, int *overflow_flag)
{
    if ((n & 1ULL) == 0ULL)
    {
        return n >> 1ULL;
    }
    else
    {
        const uint64_t max_safe_odd = (UINT64_MAX - 1ULL) / 3ULL;
        if (n > max_safe_odd)
        {
            *overflow_flag = 1;
            return 0ULL;
        }
        return 3ULL * n + 1ULL;
    }
}

// Initializes a dynamic trajectory structure
Trajectory initTrajectory(uint64_t start_val)
{
    Trajectory traj;
    traj.start_n = start_val;
    traj.peak_val = start_val;
    traj.steps = 0;
    traj.capacity = INITIAL_CAPACITY;
    traj.path = (uint64_t *)malloc(traj.capacity * sizeof(uint64_t));
    traj.overflow_occurred = 0;

    if (traj.path)
    {
        traj.path[0] = start_val;
    }
    return traj;
}

// Appends a step to the dynamic trajectory array, expanding memory as needed
void appendTrajectoryPoint(Trajectory *traj, uint64_t val)
{
    if (val > traj->peak_val)
    {
        traj->peak_val = val;
    }
    traj->steps++;

    if (traj->steps + 1 > traj->capacity)
    {
        size_t new_cap = traj->capacity * 2;
        uint64_t *new_path = (uint64_t *)realloc(traj->path, new_cap * sizeof(uint64_t));
        if (new_path)
        {
            traj->path = new_path;
            traj->capacity = new_cap;
        }
        else
        {
            fprintf(stderr, "Warning: Memory reallocation failed during trajectory growth!\n");
            return;
        }
    }
    traj->path[traj->steps] = val;
}

// Simulates trajectory from start_val down to 1
Trajectory simulateTrajectory(uint64_t start_val)
{
    Trajectory traj = initTrajectory(start_val);
    if (!traj.path)
    {
        fprintf(stderr, "Error: Memory allocation failed!\n");
        return traj;
    }

    uint64_t curr = start_val;
    int overflow = 0;

    while (curr > 1ULL)
    {
        uint64_t next = getNextCollatz(curr, &overflow);
        if (overflow)
        {
            traj.overflow_occurred = 1;
            break;
        }
        appendTrajectoryPoint(&traj, next);
        curr = next;
    }

    return traj;
}

void freeTrajectory(Trajectory *traj)
{
    if (traj->path)
    {
        free(traj->path);
        traj->path = NULL;
    }
}

// Prints the trajectory path and statistics
void printTrajectory(const Trajectory *traj, size_t max_print)
{
    printf("\n  Starting Value (n): %" PRIu64 "\n", traj->start_n);
    printf("  Stopping Time     : %zu steps\n", traj->steps);
    printf("  Peak Value Reached: %" PRIu64 "\n", traj->peak_val);

    if (traj->overflow_occurred)
    {
        printf("  [ALERT]: Arithmetic overflow detected when computing 3*n + 1!\n");
    }

    printf("  Trajectory Path   : ");
    size_t total = traj->steps + 1;
    if (total <= max_print)
    {
        for (size_t i = 0; i < total; i++)
        {
            printf("%" PRIu64 "%s", traj->path[i], (i == total - 1) ? "\n" : " -> ");
        }
    }
    else
    {
        size_t head_count = max_print / 2;
        size_t tail_count = max_print / 2;
        for (size_t i = 0; i < head_count; i++)
        {
            printf("%" PRIu64 " -> ", traj->path[i]);
        }
        printf("... [%zu intermediate values] ... -> ", total - head_count - tail_count);
        for (size_t i = total - tail_count; i < total; i++)
        {
            printf("%" PRIu64 "%s", traj->path[i], (i == total - 1) ? "\n" : " -> ");
        }
    }
}

void quickCollatzStats(uint64_t n, size_t *out_steps, uint64_t *out_peak)
{
    size_t steps = 0;
    uint64_t peak = n;
    uint64_t curr = n;
    int overflow = 0;

    while (curr > 1ULL)
    {
        curr = getNextCollatz(curr, &overflow);
        if (overflow)
        {
            break;
        }
        if (curr > peak)
        {
            peak = curr;
        }
        steps++;
    }

    *out_steps = steps;
    *out_peak = peak;
}

// Analyzes Collatz trajectories across interval [a, b]
void analyzeInterval(uint64_t a, uint64_t b)
{
    if (a > b || a == 0ULL)
    {
        printf("Error: Invalid interval [%" PRIu64 ", %" PRIu64 "]. Must have 1 <= a <= b.\n", a, b);
        return;
    }

    uint64_t count = b - a + 1ULL;
    printf("\n========================================================================\n");
    printf("   COLLATZ CONJECTURE INTERVAL ANALYSIS: [%" PRIu64 ", %" PRIu64 "]\n", a, b);
    printf("========================================================================\n");
    printf("  Total integers in range: %" PRIu64 "\n\n", count);

    uint64_t best_step_n = a;
    size_t max_steps = 0;

    uint64_t best_peak_n = a;
    uint64_t max_peak = 0;

    double total_steps = 0.0;

    int show_table = (count <= 25);
    if (show_table)
    {
        printf("    n       | Stopping Time (steps) | Peak Trajectory Value\n");
        printf(" -----------+-----------------------+-----------------------\n");
    }

    for (uint64_t n = a; n <= b; n++)
    {
        size_t steps = 0;
        uint64_t peak = 0;
        quickCollatzStats(n, &steps, &peak);

        total_steps += (double)steps;

        if (steps > max_steps)
        {
            max_steps = steps;
            best_step_n = n;
        }
        if (peak > max_peak)
        {
            max_peak = peak;
            best_peak_n = n;
        }

        if (show_table)
        {
            printf("  %9" PRIu64 " | %21zu | %21" PRIu64 "\n", n, steps, peak);
        }
    }

    printf("\n  ----------------- INTERVAL STATISTICS -----------------\n");
    printf("  Longest Trajectory in Range : n = %" PRIu64 " (with %zu steps)\n", best_step_n, max_steps);
    printf("  Highest Peak in Range       : n = %" PRIu64 " (peak value = %" PRIu64 ")\n", best_peak_n, max_peak);
    printf("  Average Stopping Time       : %.2f steps\n", total_steps / (double)count);

    printf("\n  Detailed Trajectory for Champion n = %" PRIu64 ":\n", best_step_n);
    Trajectory champ = simulateTrajectory(best_step_n);
    printTrajectory(&champ, 30);
    freeTrajectory(&champ);

    printf("========================================================================\n");
}

void runDemoCases()
{
    printf("\n--- Test 1: Single Famous Starting Point n = 27 ---\n");
    Trajectory t27 = simulateTrajectory(27);
    printTrajectory(&t27, 40);
    freeTrajectory(&t27);

    printf("\n--- Test 2: Interval Analysis [1, 20] ---\n");
    analyzeInterval(1, 20);

    printf("\n--- Test 3: Interval Analysis [100, 150] ---\n");
    analyzeInterval(100, 150);

    printf("\n--- Test 4: Famous Benchmark [900, 1000] ---\n");
    analyzeInterval(900, 1000);
}

int main(int argc, char **argv)
{
    printf("========================================================================\n");
    printf("         DAA LAB 8 - Q9: COLLATZ CONJECTURE (3n + 1 PROBLEM)            \n");
    printf("========================================================================\n");

    if (argc == 2)
    {
        uint64_t val = (uint64_t)strtoull(argv[1], NULL, 10);
        if (val >= 1ULL)
        {
            Trajectory traj = simulateTrajectory(val);
            printTrajectory(&traj, 50);
            freeTrajectory(&traj);
            return 0;
        }
    }
    else if (argc == 3)
    {
        uint64_t a = (uint64_t)strtoull(argv[1], NULL, 10);
        uint64_t b = (uint64_t)strtoull(argv[2], NULL, 10);
        analyzeInterval(a, b);
        return 0;
    }

    printf("1. Run Automated Demonstration Suite\n");
    printf("2. Analyse Single Integer Trajectory (n >= 1)\n");
    printf("3. Analyse Integer Interval [a, b]\n");
    printf("Select option (1, 2, or 3): ");

    int option = 1;
    if (scanf("%d", &option) != 1)
    {
        option = 1;
    }

    if (option == 1)
    {
        runDemoCases();
    }
    else if (option == 2)
    {
        uint64_t n;
        printf("\nEnter positive integer n: ");
        if (scanf("%" SCNu64, &n) != 1 || n < 1ULL)
        {
            printf("Invalid positive integer!\n");
            return 1;
        }
        Trajectory traj = simulateTrajectory(n);
        printTrajectory(&traj, 50);
        freeTrajectory(&traj);
    }
    else
    {
        uint64_t a, b;
        printf("\nEnter lower bound a: ");
        if (scanf("%" SCNu64, &a) != 1 || a < 1ULL)
        {
            printf("Invalid lower bound!\n");
            return 1;
        }
        printf("Enter upper bound b: ");
        if (scanf("%" SCNu64, &b) != 1 || b < a)
        {
            printf("Invalid upper bound!\n");
            return 1;
        }
        analyzeInterval(a, b);
    }

    return 0;
}