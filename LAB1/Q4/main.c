#include <stdio.h>
#include <stdlib.h>

long long steps = 0;

// TOH(number of disks, source, helper, destination)
void TOH(int n, char A, char B, char C)
{
    if (n == 0)
    {
        return;
    }

    TOH(n - 1, A, C, B);
    steps++;
    // printf("Moved disk from %c to %c\n", A, C);
    TOH(n - 1, B, A, C);
}

int main()
{
    int n;
    printf("Disks(Till which you want number of steps): ");
    scanf("%d", &n);

    FILE *file = fopen("steps_count.csv", "w");
    fprintf(file, "n,steps\n");

    for (int i = 1; i <= n; i++)
    {
        steps = 0;
        TOH(i, 'A', 'B', 'C');
        fprintf(file, "%d,%lld\n", i, steps);
        // printf("Disks: %d | Steps: %lld\n", i, steps);
    }
    
    printf("Data written successfully\n");
    fclose(file);
    // steps = (2^n) - 1
    return 0;
}