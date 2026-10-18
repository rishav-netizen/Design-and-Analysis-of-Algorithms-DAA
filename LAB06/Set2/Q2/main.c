#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

void Display(double** matrix, int n);
double** AllocateMatrix(int n);
void FreeMatrix(double** matrix, int n);
void AddMatrices(double** a, double** b, double** result, int n);
void MultiplyMatrices(double** a, double** b, double** result, int n);
int IsZeroMatrix(double** matrix, int n);
int IsSymmetric(double** matrix, int n);
void TransposeInSitu(double** matrix, int n);
double Determinant(double** matrix, int n);
void Eigen(double** matrix, int n, double* out_lambda, double* out_v);
void PrintMenu();
void InputMatrix(double** matrix, int n, const char* name);

int main()
{
    srand(time(NULL));

    int n;
    printf("Enter dimension n for n x n matrices: ");
    while (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input. Please enter a positive integer: ");
        while(getchar() != '\n');
    }

    double** A = AllocateMatrix(n);
    double** B = AllocateMatrix(n);

    printf("\nMatrix A:\n");
    InputMatrix(A, n, "A");
    
    printf("\nMatrix B:\n");
    InputMatrix(B, n, "B");
    
    // Caches
    double** AddResult = AllocateMatrix(n);
    double** MulResult = AllocateMatrix(n);
    bool add_cached = false, mul_cached = false;
    bool zero_cached = false;
    int isZeroA = 0, isZeroB = 0;
    bool sym_cached = false;
    int isSymA = 0, isSymB = 0;
    bool det_cached = false;
    double detA = 0.0, detB = 0.0;
    bool eigen_cached = false;
    double eigen_val_A = 0.0, eigen_val_B = 0.0;
    double* eigen_vec_A = (double*)malloc(n * sizeof(double));
    double* eigen_vec_B = (double*)malloc(n * sizeof(double));

    int choice;
    do
    {
        PrintMenu();
        if (scanf("%d", &choice) != 1)
        {
            while(getchar() != '\n');
            continue;
        }

        switch(choice)
        {
            case 1:
                if (!add_cached) {
                    AddMatrices(A, B, AddResult, n);
                    add_cached = true;
                }
                printf("Result of A + B:\n");
                Display(AddResult, n);
                break;
            case 2:
                if (!mul_cached) {
                    MultiplyMatrices(A, B, MulResult, n);
                    mul_cached = true;
                }
                printf("Result of A * B:\n");
                Display(MulResult, n);
                break;
            case 3:
                if (!zero_cached) {
                    isZeroA = IsZeroMatrix(A, n);
                    isZeroB = IsZeroMatrix(B, n);
                    zero_cached = true;
                }
                printf("Matrix A is %s zero matrix.\n", isZeroA ? "a" : "NOT a");
                printf("Matrix B is %s zero matrix.\n", isZeroB ? "a" : "NOT a");
                break;
            case 4:
                if (!sym_cached) {
                    isSymA = IsSymmetric(A, n);
                    isSymB = IsSymmetric(B, n);
                    sym_cached = true;
                }
                printf("Matrix A is %s symmetric.\n", isSymA ? "" : "NOT ");
                printf("Matrix B is %s symmetric.\n", isSymB ? "" : "NOT ");
                break;
            case 5:
                if (!det_cached) {
                    detA = Determinant(A, n);
                    detB = Determinant(B, n);
                    det_cached = true;
                }
                printf("Determinant of A: %.4f\n", detA);
                printf("Determinant of B: %.4f\n", detB);
                break;
            case 6:
                TransposeInSitu(A, n);
                TransposeInSitu(B, n);
                add_cached = false;
                mul_cached = false;
                zero_cached = false;
                sym_cached = false;
                det_cached = false;
                eigen_cached = false;
                printf("Matrix A transposed in-situ:\n");
                Display(A, n);
                printf("Matrix B transposed in-situ:\n");
                Display(B, n);
                break;
            case 7:
                if (!eigen_cached) {
                    Eigen(A, n, &eigen_val_A, eigen_vec_A);
                    Eigen(B, n, &eigen_val_B, eigen_vec_B);
                    eigen_cached = true;
                }
                printf("Eigen analysis for A:\n");
                printf("Dominant Eigenvalue: %.6f\n", eigen_val_A);
                printf("Corresponding Eigenvector: {");
                for (int i = 0; i < n; i++) {
                    printf("%.6f", eigen_vec_A[i]);
                    if (i < n - 1) printf(", ");
                }
                printf("}\n");
                
                printf("\nEigen analysis for B:\n");
                printf("Dominant Eigenvalue: %.6f\n", eigen_val_B);
                printf("Corresponding Eigenvector: {");
                for (int i = 0; i < n; i++) {
                    printf("%.6f", eigen_vec_B[i]);
                    if (i < n - 1) printf(", ");
                }
                printf("}\n");
                break;
            case 8:
                printf("Matrix A:\n");
                Display(A, n);
                printf("Matrix B:\n");
                Display(B, n);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    FreeMatrix(A, n);
    FreeMatrix(B, n);
    FreeMatrix(AddResult, n);
    FreeMatrix(MulResult, n);
    free(eigen_vec_A);
    free(eigen_vec_B);

    return 0;
}

void Display(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%12.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

double** AllocateMatrix(int n)
{
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

void FreeMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void AddMatrices(double** a, double** b, double** result, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void MultiplyMatrices(double** a, double** b, double** result, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int IsZeroMatrix(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fabs(matrix[i][j]) > 1e-9)
            {
                return 0;
            }
        }
    }
    return 1;
}

int IsSymmetric(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (fabs(matrix[i][j] - matrix[j][i]) > 1e-9)
            {
                return 0;
            }
        }
    }
    return 1;
}

void TransposeInSitu(double** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            double temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

double Determinant(double** matrix, int n)
{
    double** temp = AllocateMatrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = matrix[i][j];
        }
    }

    double det = 1.0;
    for (int i = 0; i < n; i++)
    {
        int pivot = i;
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
            {
                pivot = j;
            }
        }
        
        if (fabs(temp[pivot][i]) < 1e-9)
        {
            FreeMatrix(temp, n);
            return 0.0;
        }
        
        if (pivot != i)
        {
            double* t = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = t;
            det *= -1.0;
        }
        
        det *= temp[i][i];
        
        for (int j = i + 1; j < n; j++)
        {
            double factor = temp[j][i] / temp[i][i];
            for (int k = i + 1; k < n; k++)
            {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }
    
    FreeMatrix(temp, n);
    return det;
}

void Eigen(double** matrix, int n, double* out_lambda, double* out_v)
{
    double* v = (double*)malloc(n * sizeof(double));
    double* v_new = (double*)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++)
    {
        v[i] = 1.0;
    }
    
    double lambda_old = 0.0;
    double lambda_new = 0.0;
    int max_iterations = 1000;
    double tolerance = 1e-6;
    
    for (int iter = 0; iter < max_iterations; iter++)
    {
        for (int i = 0; i < n; i++)
        {
            v_new[i] = 0;
            for (int j = 0; j < n; j++)
            {
                v_new[i] += matrix[i][j] * v[j];
            }
        }
        
        lambda_new = fabs(v_new[0]);
        int max_idx = 0;
        for (int i = 1; i < n; i++)
        {
            if (fabs(v_new[i]) > lambda_new)
            {
                lambda_new = fabs(v_new[i]);
                max_idx = i;
            }
        }
        lambda_new = v_new[max_idx];
        
        if (fabs(lambda_new) < 1e-9) break;
        
        for (int i = 0; i < n; i++)
        {
            v_new[i] /= lambda_new;
        }
        
        double diff = fabs(lambda_new - lambda_old);
        if (diff < tolerance)
        {
            break;
        }
        
        lambda_old = lambda_new;
        for (int i = 0; i < n; i++)
        {
            v[i] = v_new[i];
        }
    }
    
    *out_lambda = lambda_new;
    for (int i = 0; i < n; i++)
    {
        out_v[i] = v_new[i];
    }
    
    free(v);
    free(v_new);
}

void PrintMenu()
{
    printf("\n--- 2D Square Matrix Operations ---\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Zero Check\n");
    printf("4. Symmetric Check\n");
    printf("5. Determinant\n");
    printf("6. Transpose in-situ\n");
    printf("7. Dominant Eigenvalue/Eigenvector (Power Method)\n");
    printf("8. Display Matrices\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

void InputMatrix(double** matrix, int n, const char* name)
{
    int choice;
    printf("Choose input method for Matrix %s (1 for manual, 2 for random): ", name);
    while (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid input. Try again: ");
        while(getchar() != '\n');
    }

    if (choice == 1)
    {
        printf("Enter elements for Matrix %s (%dx%d):\n", name, n, n);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                printf("%s[%d][%d]: ", name, i, j);
                while (scanf("%lf", &matrix[i][j]) != 1)
                {
                    printf("Invalid input. Enter %s[%d][%d]: ", name, i, j);
                    while(getchar() != '\n');
                }
            }
        }
    }
    else
    {
        double lower, upper;
        printf("Enter limits (min and max) for random numbers: ");
        while (scanf("%lf %lf", &lower, &upper) != 2 || lower > upper)
        {
            printf("Invalid limits. Try again (min max): ");
            while(getchar() != '\n');
        }
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                double r = (double)rand() / RAND_MAX;
                matrix[i][j] = round(lower + r * (upper - lower));
            }
        }
        printf("Matrix %s filled with random values between %.2f and %.2f.\n", name, lower, upper);
    }
}

