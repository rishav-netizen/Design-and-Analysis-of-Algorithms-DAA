#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strcmp for --benchmark
#include <time.h>

int *merge(const int left[], int left_size, const int right[], int right_size)
{
    int *result = malloc((left_size + right_size) * sizeof(int));
    int i = 0, j = 0, k = 0;

    if (result == NULL) return NULL;
    while (i < left_size && j < right_size)
        result[k++] = (left[i] <= right[j]) ? left[i++] : right[j++];
    while (i < left_size) result[k++] = left[i++];
    while (j < right_size) result[k++] = right[j++];
    return result;
}

/* Split the list of arrays in half, then merge the two answers. */
int *balanced_merge(int *arrays[], int first, int last, int n)
{
    int middle, left_count, right_count;
    int *left, *right, *result;

    if (first == last) {
        result = malloc(n * sizeof(int));
        for (int i = 0; result != NULL && i < n; i++)
            result[i] = arrays[first][i];
        return result;
    }

    middle = (first + last) / 2;
    left = balanced_merge(arrays, first, middle, n);
    right = balanced_merge(arrays, middle + 1, last, n);
    if (left == NULL || right == NULL) { free(left); free(right); return NULL; }
    left_count = (middle - first + 1) * n;
    right_count = (last - middle) * n;
    result = merge(left, left_count, right, right_count);
    free(left); free(right);
    return result;
}

int **make_arrays(int k, int n)
{
    int **arrays = malloc(k * sizeof(int *));
    if (arrays == NULL) return NULL;
    for (int i = 0; i < k; i++) {
        arrays[i] = malloc(n * sizeof(int));
        if (arrays[i] == NULL) {
            while (i-- > 0) free(arrays[i]);
            free(arrays);
            return NULL;
        }
        for (int j = 0; j < n; j++) arrays[i][j] = i + j * k;
    }
    return arrays;
}

void free_arrays(int *arrays[], int k)
{
    if (arrays == NULL) return;
    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);
}

int sorted(int a[], int size)
{
    for (int i = 1; i < size; i++) if (a[i - 1] > a[i]) return 0;
    return 1;
}

void print_array(const int a[], int size)
{
    printf("[");
    for (int i = 0; i < size; i++) printf("%d%s", a[i], i + 1 == size ? "" : ", ");
    printf("]\n");
}

int benchmark(int k, int n, int trials)
{
    int **arrays = make_arrays(k, n);
    double total = 0.0;
    int okay = 1;

    if (arrays == NULL) return EXIT_FAILURE;
    for (int t = 0; t < trials; t++) {
        clock_t start = clock();
        int *result = balanced_merge(arrays, 0, k - 1, n);
        total += (double)(clock() - start) / CLOCKS_PER_SEC;
        okay = okay && result != NULL && sorted(result, k * n);
        free(result);
    }
    printf("k,n,total_elements,average_seconds,sorted\n");
    printf("%d,%d,%d,%.9f,%s\n", k, n, k * n, total / trials, okay ? "true" : "false");
    free_arrays(arrays, k);
    return okay ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(int argc, char *argv[])
{
    int k, n;

    if (argc == 5 && strcmp(argv[1], "--benchmark") == 0) {
        k = atoi(argv[2]); n = atoi(argv[3]);
        if (k > 0 && n > 0 && atoi(argv[4]) > 0)
            return benchmark(k, n, atoi(argv[4]));
        return EXIT_FAILURE;
    }

    printf("Balanced pairwise merge of k sorted arrays\nEnter k: ");
    if (scanf("%d", &k) != 1 || k < 1) return EXIT_FAILURE;
    printf("Enter n (elements in each array): ");
    if (scanf("%d", &n) != 1 || n < 1) return EXIT_FAILURE;

    int **arrays = make_arrays(k, n);
    int *result = arrays == NULL ? NULL : balanced_merge(arrays, 0, k - 1, n);
    if (result == NULL) { free_arrays(arrays, k); return EXIT_FAILURE; }
    if (k * n <= 80) print_array(result, k * n);
    printf("Verification: output is %ssorted.\n", sorted(result, k * n) ? "" : "NOT ");
    free(result); free_arrays(arrays, k);
    return EXIT_SUCCESS;
}
