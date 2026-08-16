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
    return (Matrix){n, calloc((size_t)n * n, sizeof(long long))};
}

static void freeMatrix(Matrix matrix)
{
    free(matrix.value);
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

static Matrix add(Matrix a, Matrix b)
{
    Matrix result = makeMatrix(a.n);
    for (int i = 0; i < a.n * a.n; i++)
        result.value[i] = a.value[i] + b.value[i];
    return result;
}

static int isSpecial(Matrix matrix)
{
    if (matrix.n == 1)
        return 1;

    int half = matrix.n / 2;
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++)
            if (AT(matrix, i, j) != AT(matrix, i + half, j + half) ||
                AT(matrix, i, j + half) != AT(matrix, i + half, j))
                return 0;

    Matrix diagonal = quadrant(matrix, 0, 0);
    Matrix offDiagonal = quadrant(matrix, 0, half);
    int valid = isSpecial(diagonal) && isSpecial(offDiagonal);
    freeMatrix(diagonal);
    freeMatrix(offDiagonal);
    return valid;
}

/* For [A B; B A] and [C D; D C], the result is [P Q; Q P]. */
static Matrix multiplySpecial(Matrix left, Matrix right)
{
    if (left.n == 1)
    {
        Matrix result = makeMatrix(1);
        result.value[0] = left.value[0] * right.value[0];
        return result;
    }

    int half = left.n / 2;
    Matrix a = quadrant(left, 0, 0);
    Matrix b = quadrant(left, 0, half);
    Matrix c = quadrant(right, 0, 0);
    Matrix d = quadrant(right, 0, half);

    Matrix ac = multiplySpecial(a, c);
    Matrix bd = multiplySpecial(b, d);
    Matrix p = add(ac, bd);
    Matrix ad = multiplySpecial(a, d);
    Matrix bc = multiplySpecial(b, c);
    Matrix q = add(ad, bc);

    Matrix result = makeMatrix(left.n);
    for (int i = 0; i < half; i++)
        for (int j = 0; j < half; j++)
        {
            AT(result, i, j) = AT(p, i, j);
            AT(result, i, j + half) = AT(q, i, j);
            AT(result, i + half, j) = AT(q, i, j);
            AT(result, i + half, j + half) = AT(p, i, j);
        }

    freeMatrix(a); freeMatrix(b); freeMatrix(c); freeMatrix(d);
    freeMatrix(ac); freeMatrix(bd); freeMatrix(ad); freeMatrix(bc);
    freeMatrix(p); freeMatrix(q);
    return result;
}

static int isPowerOfTwo(int n)
{
    return n > 0 && (n & (n - 1)) == 0;
}

static void readMatrix(Matrix matrix, const char *name)
{
    printf("Enter matrix %s (%d x %d):\n", name, matrix.n, matrix.n);
    for (int i = 0; i < matrix.n; i++)
        for (int j = 0; j < matrix.n; j++)
            scanf("%lld", &AT(matrix, i, j));
}

int main(void)
{
    int n;
    printf("Enter n (a power of 2): ");
    if (scanf("%d", &n) != 1 || !isPowerOfTwo(n))
    {
        printf("n must be a positive power of 2.\n");
        return 1;
    }

    Matrix a = makeMatrix(n);
    Matrix b = makeMatrix(n);
    if (a.value == NULL || b.value == NULL)
    {
        freeMatrix(a); freeMatrix(b);
        return 1;
    }

    readMatrix(a, "A");
    readMatrix(b, "B");
    if (!isSpecial(a) || !isSpecial(b))
    {
        printf("Both matrices must satisfy the recursive [M1 M2; M2 M1] pattern.\n");
        freeMatrix(a); freeMatrix(b);
        return 1;
    }

    Matrix product = multiplySpecial(a, b);
    printf("Product:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%lld ", AT(product, i, j));
        printf("\n");
    }

    freeMatrix(a); freeMatrix(b); freeMatrix(product);
    return 0;
}
