# Q5 - Multiplying Special-Pattern Matrices

The input matrices must recursively follow this form:

```text
M = [ M1  M2 ]
    [ M2  M1 ]
```

For matrices `A = [A1 A2; A2 A1]` and `B = [B1 B2; B2 B1]`, the product is also special:

```text
AB = [ P  Q ]
     [ Q  P ]

P = A1B1 + A2B2
Q = A1B2 + A2B1
```

The program checks that both inputs follow the pattern before multiplying them.

```sh
cc -std=c11 -Wall -Wextra main.c -o q5
./q5
```

There are four recursive multiplications on matrices of size `n/2`, plus `O(n^2)` work to add and assemble blocks. Thus `T(n) = 4T(n/2) + O(n^2) = O(n^2)`.
