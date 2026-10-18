#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void Display(int* arr, int n);
int MatrixChainMultiplication(int* arr, int n);

int main()
{
    int n;

    while (1)
    {
        printf("Enter the number of elements in the dimensions array (minimum 2): ");
        if (scanf("%d", &n) == 1 && n >= 2)
        {
            break;
        }
        else
        {
            printf("Invalid input. Please enter an integer >= 2.\n");
            while(getchar() != '\n'); // clear input buffer
        }
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter the elements of the dimensions array:\n");
    for (int i = 0; i < n; i++)
    {
        while (1)
        {
            printf("Element %d: ", i + 1);
            if (scanf("%d", &arr[i]) == 1 && arr[i] > 0)
            {
                break;
            }
            else
            {
                printf("Invalid input. Please enter a positive integer.\n");
                while(getchar() != '\n'); // clear input buffer
            }
        }
    }

    printf("Dimensions array: ");
    Display(arr, n);

    int result = MatrixChainMultiplication(arr, n);
    printf("Minimum number of scalar multiplications: %d\n", result);

    free(arr);
    return 0;
}

void Display(int* arr, int n)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}

int MatrixChainMultiplication(int* arr, int n)
{
    // The number of matrices is n - 1
    // m[i][j] will store the minimum number of scalar multiplications
    // needed to compute the matrix A[i]A[i+1]...A[j]
    int num_matrices = n - 1;
    
    int** m = (int**)malloc((n) * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        m[i] = (int*)malloc((n) * sizeof(int));
    }

    for (int i = 1; i <= num_matrices; i++)
    {
        m[i][i] = 0;
    }

    for (int L = 2; L <= num_matrices; L++)
    {
        for (int i = 1; i <= num_matrices - L + 1; i++)
        {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                }
            }
        }
    }

    int min_mults = m[1][num_matrices];

    for (int i = 0; i < n; i++)
    {
        free(m[i]);
    }
    free(m);

    return min_mults;
}

