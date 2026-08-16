#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int n;
    long long *value;
} Matrix;

#define AT(matrix, row, column) ((matrix).value[(size_t)(row) * (matrix).n + (column)])

static Matrix makeMatrix(int n)
{
    Matrix matrix = {n, calloc((size_t)n * n, sizeof(*matrix.value))};
    return matrix;
}

static void freeMatrix(Matrix matrix)
{
    free(matrix.value);
}

static Matrix add(Matrix a, Matrix b)
{
    Matrix result = makeMatrix(a.n);
    for (int i = 0; i < a.n * a.n; i++)
        result.value[i] = a.value[i] + b.value[i];
    return result;
}

static Matrix subtract(Matrix a, Matrix b)
{
    Matrix result = makeMatrix(a.n);
    for (int i = 0; i < a.n * a.n; i++)
        result.value[i] = a.value[i] - b.value[i];
    return result;
}

static Matrix quadrant(Matrix matrix, int rowOffset, int columnOffset)
{
    int half = matrix.n / 2;
    Matrix result = makeMatrix(half);
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++)
            AT(result, i, j) = AT(matrix, i + rowOffset, j + columnOffset);
    return result;
}

static Matrix strassen(Matrix a, Matrix b)
{
    if (a.n == 1)
    {
        Matrix result = makeMatrix(1);
        result.value[0] = a.value[0] * b.value[0];
        return result;
    }

    int half = a.n / 2;
    Matrix a11 = quadrant(a, 0, 0), a12 = quadrant(a, 0, half);
    Matrix a21 = quadrant(a, half, 0), a22 = quadrant(a, half, half);
    Matrix b11 = quadrant(b, 0, 0), b12 = quadrant(b, 0, half);
    Matrix b21 = quadrant(b, half, 0), b22 = quadrant(b, half, half);

    Matrix x = add(a11, a22), y = add(b11, b22);
    Matrix p1 = strassen(x, y); freeMatrix(x); freeMatrix(y);
    x = add(a21, a22); Matrix p2 = strassen(x, b11); freeMatrix(x);
    x = subtract(b12, b22); Matrix p3 = strassen(a11, x); freeMatrix(x);
    x = subtract(b21, b11); Matrix p4 = strassen(a22, x); freeMatrix(x);
    x = add(a11, a12); Matrix p5 = strassen(x, b22); freeMatrix(x);
    x = subtract(a21, a11); y = add(b11, b12);
    Matrix p6 = strassen(x, y); freeMatrix(x); freeMatrix(y);
    x = subtract(a12, a22); y = add(b21, b22);
    Matrix p7 = strassen(x, y); freeMatrix(x); freeMatrix(y);

    Matrix result = makeMatrix(a.n);
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++)
        {
            AT(result, i, j) = AT(p1, i, j) + AT(p4, i, j) - AT(p5, i, j) + AT(p7, i, j);
            AT(result, i, j + half) = AT(p3, i, j) + AT(p5, i, j);
            AT(result, i + half, j) = AT(p2, i, j) + AT(p4, i, j);
            AT(result, i + half, j + half) = AT(p1, i, j) - AT(p2, i, j) + AT(p3, i, j) + AT(p6, i, j);
        }

    freeMatrix(a11); freeMatrix(a12); freeMatrix(a21); freeMatrix(a22);
    freeMatrix(b11); freeMatrix(b12); freeMatrix(b21); freeMatrix(b22);
    freeMatrix(p1); freeMatrix(p2); freeMatrix(p3); freeMatrix(p4);
    freeMatrix(p5); freeMatrix(p6); freeMatrix(p7);
    return result;
}

static int nextPowerOfTwo(int n)
{
    int power = 1;
    while (power < n)
        power *= 2;
    return power;
}

static void readMatrix(Matrix matrix, int originalSize, const char *name)
{
    printf("Enter matrix %s (%d x %d):\n", name, originalSize, originalSize);
    for (int i = 0; i < originalSize; i++)
        for (int j = 0; j < originalSize; j++)
            scanf("%lld", &AT(matrix, i, j));
}

int main(void)
{
    int n;
    printf("Enter square matrix size: ");
    if (scanf("%d", &n) != 1 || n < 1)
        return 1;

    int paddedSize = nextPowerOfTwo(n);
    Matrix a = makeMatrix(paddedSize);
    Matrix b = makeMatrix(paddedSize);
    if (a.value == NULL || b.value == NULL)
    {
        freeMatrix(a); freeMatrix(b);
        return 1;
    }

    readMatrix(a, n, "A");
    readMatrix(b, n, "B");
    Matrix product = strassen(a, b);

    printf("A x B:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%lld ", AT(product, i, j));
        printf("\n");
    }

    freeMatrix(a); freeMatrix(b); freeMatrix(product);
    return 0;
}
