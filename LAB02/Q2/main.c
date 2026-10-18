#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define START_SIZE 256
#define DEFAULT_MAX_SIZE 262144
#define DEFAULT_TRIALS 7

// Merge the sorted parts a[left..mid] and a[mid+1..right].
void merge_two_way(int a[], int temp[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right)
        temp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= right)
        temp[k++] = a[j++];

    for (i = left; i <= right; i++)
        a[i] = temp[i];
}

void merge_sort(int a[], int temp[], int left, int right)
{
    int mid;

    if (left >= right)
        return;

    mid = left + (right - left) / 2;
    merge_sort(a, temp, left, mid);
    merge_sort(a, temp, mid + 1, right);
    merge_two_way(a, temp, left, mid, right);
}

// Merge three sorted parts: [left..mid1], [mid1+1..mid2], [mid2+1..right].
void merge_three_way(int a[], int temp[], int left, int mid1, int mid2, int right)
{
    int i = left, j = mid1 + 1, k = mid2 + 1, out = left;

    while (i <= mid1 || j <= mid2 || k <= right) {
        int smallest = 0;
        int source = 0;

        if (i <= mid1 && (source == 0 || a[i] < smallest)) {
            smallest = a[i];
            source = 1;
        }
        if (j <= mid2 && (source == 0 || a[j] < smallest)) {
            smallest = a[j];
            source = 2;
        }
        if (k <= right && (source == 0 || a[k] < smallest)) {
            smallest = a[k];
            source = 3;
        }

        temp[out++] = smallest;
        if (source == 1)
            i++;
        else if (source == 2)
            j++;
        else
            k++;
    }

    for (i = left; i <= right; i++)
        a[i] = temp[i];
}

void three_way_merge_sort(int a[], int temp[], int left, int right)
{
    int size, mid1, mid2;

    if (left >= right)
        return;

    size = right - left + 1;
    mid1 = left + (size / 3) - 1;
    mid2 = left + (2 * (size / 3)) - 1;


    if (mid1 < left)
        mid1 = left;
    if (mid2 < mid1 + 1)
        mid2 = mid1 + 1;
    if (mid2 > right)
        mid2 = right;

    three_way_merge_sort(a, temp, left, mid1);
    three_way_merge_sort(a, temp, mid1 + 1, mid2);
    three_way_merge_sort(a, temp, mid2 + 1, right);
    merge_three_way(a, temp, left, mid1, mid2, right);
}

int is_sorted(int a[], int n) // checks if array is sorted in ascending order
{
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            return 0;
    return 1;
}

void fill_random(int a[], int n) // to make arrays filled with random numbers
{
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

double benchmark(void (*sort)(int[], int[], int, int), int original[],
                 int a[], int temp[], int n, int trials)
{
    double total = 0.0;

    for (int trial = 0; trial < trials; trial++) {
        clock_t start, end;
        for (int i = 0; i < n; i++)
            a[i] = original[i];
        start = clock();
        sort(a, temp, 0, n - 1);
        end = clock();
        total += (double)(end - start) / CLOCKS_PER_SEC;

        if (!is_sorted(a, n)) {
            fprintf(stderr, "Sorting failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    return total / trials;
}

int main(int argc, char *argv[])
{
    int max_size = DEFAULT_MAX_SIZE;
    int trials = DEFAULT_TRIALS;
    const char *csv_name = "data/benchmark_results.csv";
    FILE *file;
    int *original, *a, *temp;

    if (argc > 1)
        max_size = atoi(argv[1]);
    if (argc > 2)
        trials = atoi(argv[2]);
    if (argc > 3)
        csv_name = argv[3];
    if (max_size < START_SIZE || trials < 1) {
        fprintf(stderr, "Usage: %s [maximum size >= %d] [trials] [csv file]\n",
                argv[0], START_SIZE);
        return EXIT_FAILURE;
    }

    original = malloc(max_size * sizeof(int));
    a = malloc(max_size * sizeof(int));
    temp = malloc(max_size * sizeof(int));
    file = fopen(csv_name, "w");
    if (original == NULL || a == NULL || temp == NULL || file == NULL) {
        fprintf(stderr, "Could not create the benchmark.\n");
        free(original); free(a); free(temp);
        if (file != NULL) fclose(file);
        return EXIT_FAILURE;
    }

    srand(42);
    fprintf(file, "n,two_way_seconds,three_way_seconds\n");
    printf("%10s | %12s | %12s\n", "n", "two-way", "three-way");
    printf("-----------|--------------|--------------\n");

    for (int n = START_SIZE; n <= max_size; n *= 2) {
        double two_way, three_way;
        fill_random(original, n);
        two_way = benchmark(merge_sort, original, a, temp, n, trials);
        three_way = benchmark(three_way_merge_sort, original, a, temp, n, trials);
        fprintf(file, "%d,%.9f,%.9f\n", n, two_way, three_way);
        printf("%10d | %12.6f | %12.6f\n", n, two_way, three_way);
        if (n > max_size / 2)
            break;
    }

    fclose(file);
    free(original); free(a); free(temp);
    printf("\nResults saved to %s\n", csv_name);
    return EXIT_SUCCESS;
}
