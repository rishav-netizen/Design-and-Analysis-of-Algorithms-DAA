#include <stdio.h>
#include <math.h>

typedef char* string;

enum Function {
    ONE_OVER_N,
    LOG2_N,
    SQRT12_N,
    N_POW_0_51,
    SQRT50_N,
    TWO_POW_32_N,
    N_LOG2_N,
    HUNDRED_N2_PLUS_6N,
    N2_MINUS_324,
    TWO_N3,
    N_POW_LOG2_N,
    THREE_POW_N,
    NUM_FUNCTIONS
};

const string function_names[NUM_FUNCTIONS] = {
    "1/n",
    "log2(n)",
    "12sqrt(n)",
    "n^0.51",
    "50sqrt(n)",
    "2^32 * n",
    "n log2(n)",
    "100n^2 + 6n",
    "n^2 - 324",
    "2n^3",
    "n^(log2 n)",
    "3^n"
};

int main() {
    FILE *f = fopen("q1_data.csv", "w");

    if (f == NULL) {
        printf("Error creating file.\n");
        return 1;
    }

    fprintf(f, "n,1_over_n,log2_n,12sqrt_n,n_pow_0_51,50sqrt_n,2pow32_n,nlog2n,100n2_plus_6n,n2_minus_324,2n3,n_log2_n,3_pow_n\n");
    
    for (int n = 1; n <= 200; n++) {
        fprintf(f,
                "%d,%lf,%lf,%lf,%lf,%lf,%.0lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                n,
                1.0 / n,
                log2((double)n),
                12 * sqrt((double)n),
                pow((double)n, 0.51),
                50 * sqrt((double)n),
                pow(2.0, 32) * n,
                n * log2((double)n),
                100 * pow((double)n, 2) + 6 * n,
                pow((double)n, 2) - 324,
                2 * pow((double)n, 3),
                pow((double)n, log2((double)n)),
                pow(3.0, n));
    }

    printf("\nIncreasing Order of Growth (for sufficiently large n):\n\n");

    int order[] = {
        ONE_OVER_N,
        LOG2_N,
        SQRT12_N,
        SQRT50_N,
        N_POW_0_51,
        TWO_POW_32_N,
        N_LOG2_N,
        HUNDRED_N2_PLUS_6N,
        N2_MINUS_324,
        TWO_N3,
        N_POW_LOG2_N,
        THREE_POW_N
    };

    for (int i = 0; i < NUM_FUNCTIONS; i++) {
        printf("%2d. %s\n", i + 1, function_names[order[i]]);
    }

    printf("\nNote: 12sqrt(n) & 50sqrt(n), and 100n^2+6n & n^2-324 belong to the same asymptotic growth class; they are listed separately only because they are separate functions in the assignment.\n");

    fclose(f);
    printf("Data written to q1_data.csv successfully.\n");
    return 0;
}