# Q3 - Maximum and Minimum using Divide and Conquer

The array is split into two parts. Each recursive call returns both its minimum and maximum. The two results are merged using only two comparisons.

```sh
cc -std=c11 -Wall -Wextra main.c -o q3
./q3
```

For a power-of-two input size, it uses `3n/2 - 2` comparisons. More generally the number remains bounded by about `3n/2`, which is better than finding the minimum and maximum separately.
