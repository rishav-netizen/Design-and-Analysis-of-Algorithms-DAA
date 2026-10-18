# Q1 - Binary vs Ternary Search

`fun.c` creates distinct numbers, shuffles them, sorts them, and searches every number using both methods. The comparison count for each search is stored in an array, then averaged for each input size.

Binary search uses one three-way comparison at each midpoint. Ternary search checks two midpoints, so it needs more comparisons on average even though it removes a larger fraction of the array each round.

```sh
cc -std=c11 -Wall -Wextra fun.c -o fun
./fun
```

Time complexity: binary search is `O(log n)` and ternary search is also `O(log n)`. In this comparison model, binary search has the smaller constant factor.
