#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillRatingsRandomly(int n, int *ratings, int u, int l);
int randomBtw(int u, int l);
void display(int n, int *array);

int main(){
    int n;
    printf("Enter the number of children: ");
    scanf("%d", &n);
    while (n <= 0)
    {
        printf("Invalid input try again: ");
        scanf("%d", &n);
    }

    int *ratings = calloc(n, sizeof(int));
    int choice;
    printf("Do you wanna: \t(0) Enter ratings or\n\t\t(1) Have it randomly filled?\nChoice: ");
    
    scanf("%d", &choice);
    while (choice != 0 && choice != 1)
    {
        printf("Invalid Input try again: ");
        scanf("%d", &choice);
    }

    int u, l;
    switch (choice)
    {
        case 0:
            {
                printf("Enter the ratings: ");
                for (int i = 0; i < n; i++)
                {
                    scanf("%d", ratings + i);
                }
                break;
            }

        case 1:
            {
                printf("Enter the lower and upper limits for random ratings: ");
                scanf("%d %d", &l, &u);
                while (l >= u)
                {
                    printf("Invalid input try again: ");
                    scanf("%d %d", &l, &u);
                }
                fillRatingsRandomly(n, ratings, u, l);
            }

        default:
            break;
    }


    printf("The ratings of the children are: ");
    display(n, ratings);

    int *candies = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        candies[i] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        if (ratings[i] > ratings[i - 1])
        {
            candies[i] = candies[i - 1] + 1;
        }
    }
    for (int i = n - 2; i >= 0; i--)
    {
        if (ratings[i + 1] < ratings[i])
        {
            if (candies[i] < candies[i + 1] + 1)
            {   
                candies[i] = candies[i + 1] + 1;
            }
        }
    }
    
    printf("The candies to each child is: ");
    display(n, candies);

    return 0;
}

void fillRatingsRandomly(int n, int *ratings, int u, int l)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        ratings[i] = randomBtw(u, l);
    }
}

int randomBtw(int u, int l)
{
    return (rand() % (u - l)) + l;
}

void display(int n, int *array)
{
    printf("{");
    for (int i = 0; i < n; i++)
    {
        printf("%d", array[i]);
        if (i < n - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}