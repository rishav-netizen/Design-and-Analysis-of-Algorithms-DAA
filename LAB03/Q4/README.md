# Q4 - Matrix Multiplication using Strassen's Method

This program multiplies two square matrices using Strassen's divide-and-conquer method. It splits each matrix into four blocks and uses seven recursive multiplications instead of the usual eight. If the input size is not a power of two, the matrices are padded with zeroes internally and only the original-size result is printed.

```sh
cc -std=c11 -Wall -Wextra main.c -o q4
./q4
```

For example, multiplying `1 2 / 3 4` by `5 6 / 7 8` gives `19 22 / 43 50`.

The recurrence is `T(n) = 7T(n/2) + O(n^2)`, so the time complexity is `O(n^log2(7))`, approximately `O(n^2.81)`.
