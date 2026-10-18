#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

void Display(ll *arr, ll l);

int main()
{
    ll n;
    printf("Enter which fibonacci number you wanna get: ");
    scanf("%lld", &n);

    // zero initialized
    ll *F = calloc(n + 1, sizeof(ll));

    F[0] = 0;

    if (n >= 1)
        F[1] = 1;

    for (ll i = 2; i <= n; i++)
    {
        F[i] += F[i-1] + F[i-2]; // we can add since zero initialized
    }
    
    printf("F(%lld) = %lld\n", n, F[n]);
    // Display(F, n + 1);

    free(F);

    return 0;
}

void Display(ll *arr, ll l)
{
    printf("{");
    for (int i = 0; i < l; i++)
    {
        printf("%lld", arr[i]);
        if (i < l - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");
}