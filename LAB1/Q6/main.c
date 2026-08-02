#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int random_between(int lowerLimit, int upperLimit);
void Display(int *array, int length);

int main(void)
{
    // This makes the sequence pseudo-random based on the current time.
    long elapsedSeconds = time(NULL); // Seconds since Jan 1, 1970
    srand((unsigned int)elapsedSeconds);

    int lowerLimit, upperLimit;
    printf("Enter the limits between which the random number should be:\n");
    printf("Enter the lower limit: ");
    scanf("%d", &lowerLimit);
    printf("Enter the upper limit: ");
    scanf("%d", &upperLimit);
    if (lowerLimit > upperLimit)
    {
        printf("Invalid range! Lower limit must be less than or equal to upper limit.\n");
        return 1;
    }

    int n;
    printf("How many random numbers you wanna generate: ");
    scanf("%d", &n);

    int randoms[n];
    
    for(int i = 0; i < n; i++)
    {
        int number = random_between(lowerLimit, upperLimit);
        randoms[i] = number;
        // printf("%d\n", number);
    }
    
    int *frequency;
    int size = upperLimit + 1; //because i wanted to make the index have same value as number
    frequency = calloc((size), sizeof(int)); // so that all are assigned to 0

    for (int i = 0; i < n; i++)
    {
        frequency[randoms[i]]++;
    }
    // Display(frequency, size); //just used for checking 

    FILE *file = fopen("randoms_count.csv", "w");
    if (file == NULL)
    {
        free(frequency);
        printf("Could not open file!\n");
        return 1;
    }
    
    fprintf(file, "Numbers,Frequency\n");
    for (int i = lowerLimit; i < upperLimit + 1; i++)
    {
        fprintf(file, "%d,%d\n", i, frequency[i]);
    }
    
    free(frequency);
    fclose(file);
    return 0;
}

int random_between(int lowerLimit, int upperLimit)
{
    return rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
}

void Display(int *array, int length)
{
    printf("{");
    for (int i = 0; i < length; i++)
    {
        printf("%d", array[i]);
        if(i < length - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}