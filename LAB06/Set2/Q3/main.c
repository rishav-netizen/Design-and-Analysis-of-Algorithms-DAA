#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.141592

void Display(int* arr, int n);
void Fft(double complex* a, int n, int invert);
int NextPowerOf2(int n);

int main()
{
    int m, n;
    
    printf("Enter size of vector A: ");
    if (scanf("%d", &m) != 1) return 1;
    
    int* A = (int*)malloc(m * sizeof(int));
    if (A == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return 1;
    }
    
    printf("Enter elements of A: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &A[i]);
    }
    
    printf("Enter size of vector B: ");
    if (scanf("%d", &n) != 1) return 1;
    
    int* B = (int*)malloc(n * sizeof(int));
    if (B == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(A);
        return 1;
    }
    
    printf("Enter elements of B: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &B[i]);
    }
    
    int out_size = m + n - 1;
    int N = NextPowerOf2(out_size);
    
    double complex* fa = (double complex*)calloc(N, sizeof(double complex));
    if (fa == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(A);
        free(B);
        return 1;
    }

    double complex* fb = (double complex*)calloc(N, sizeof(double complex));
    if (fb == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(A);
        free(B);
        free(fa);
        return 1;
    }
    
    for (int i = 0; i < m; i++)
        fa[i] = A[i];
    for (int i = 0; i < n; i++)
        fb[i] = B[i];
        
    Fft(fa, N, 0);
    Fft(fb, N, 0);
    
    for (int i = 0; i < N; i++)
    {
        fa[i] *= fb[i];
    }
    
    Fft(fa, N, 1);
    
    int* result = (int*)malloc(out_size * sizeof(int));
    if (result == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(A);
        free(B);
        free(fa);
        free(fb);
        return 1;
    }
    for (int i = 0; i < out_size; i++)
    {
        result[i] = (int)round(creal(fa[i]) / N);
    }
    
    printf("Vector A: ");
    Display(A, m);
    
    printf("Vector B: ");
    Display(B, n);
    
    printf("Convolution Result: ");
    Display(result, out_size);
    
    free(A);
    free(B);
    free(fa);
    free(fb);
    free(result);
    
    return 0;
}

void Display(int* arr, int n)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("}\n");
}

void Fft(double complex* a, int n, int invert)
{
    if (n == 1) return;
    
    double complex* a0 = (double complex*)malloc((n / 2) * sizeof(double complex));
    if (a0 == NULL)
    {
        printf("Memory Allocation Failed!\n");
        return;
    }

    double complex* a1 = (double complex*)malloc((n / 2) * sizeof(double complex));
    if (a1 == NULL)
    {
        printf("Memory Allocation Failed!\n");
        free(a0);
        return;
    }
    
    for (int i = 0; 2 * i < n; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    
    Fft(a0, n / 2, invert);
    Fft(a1, n / 2, invert);
    
    for (int i = 0; 2 * i < n; i++)
    {
        double angle = 2 * PI * i / n * (invert ? -1 : 1);
        double complex w = cos(angle) + sin(angle) * I;
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
    }
    
    free(a0);
    free(a1);
}

int NextPowerOf2(int n)
{
    int p = 1;
    while (p < n)
        p <<= 1;
    return p;
}

