#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Display(int* arr, int n);
int Max(int a, int b);
void LongestCommonSubsequence(char* str1, char* str2);

int main()
{
    int max_len = 1000;
    char* str1 = (char*)malloc(max_len * sizeof(char));
    char* str2 = (char*)malloc(max_len * sizeof(char));

    if (str1 == NULL || str2 == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (1)
    {
        printf("Enter the first string (max %d characters): ", max_len - 1);
        if (scanf("%s", str1) == 1)
        {
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
            while(getchar() != '\n'); // clear input buffer
        }
    }

    while (1)
    {
        printf("Enter the second string (max %d characters): ", max_len - 1);
        if (scanf("%s", str2) == 1)
        {
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
            while(getchar() != '\n'); // clear input buffer
        }
    }

    LongestCommonSubsequence(str1, str2);

    free(str1);
    free(str2);

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

int Max(int a, int b)
{
    return (a > b) ? a : b;
}

void LongestCommonSubsequence(char* str1, char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int** dp = (int**)malloc((len1 + 1) * sizeof(int*));
    for (int i = 0; i <= len1; i++)
    {
        dp[i] = (int*)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++)
    {
        for (int j = 0; j <= len2; j++)
        {
            if (i == 0 || j == 0)
            {
                dp[i][j] = 0;
            }
            else if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = Max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int lcs_length = dp[len1][len2];
    printf("Length of Longest Common Subsequence: %d\n", lcs_length);

    char* lcs = (char*)malloc((lcs_length + 1) * sizeof(char));
    lcs[lcs_length] = '\0';

    int i = len1;
    int j = len2;
    int index = lcs_length - 1;

    while (i > 0 && j > 0)
    {
        if (str1[i - 1] == str2[j - 1])
        {
            lcs[index] = str1[i - 1];
            i--;
            j--;
            index--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("Longest Common Subsequence: %s\n", lcs);

    for (int k = 0; k <= len1; k++)
    {
        free(dp[k]);
    }
    free(dp);
    free(lcs);
}

