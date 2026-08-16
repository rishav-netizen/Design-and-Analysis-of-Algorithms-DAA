# Q6 - Selection Sort and its Loop Invariant

The program implements the sorting method in the question: find the smallest item in the unsorted suffix and exchange it with the first item of that suffix.

Pseudocode:

```text
for i = 0 to n - 2
    min = i
    for j = i + 1 to n - 1
        if A[j] < A[min]
            min = j
    swap A[i], A[min]
```

Loop invariant: before each outer-loop iteration `i`, `A[0..i-1]` contains the `i` smallest elements in sorted order. Initially this part is empty. Selecting the smallest remaining item maintains it. After `n - 1` passes, the final item must already be the largest, so another pass is unnecessary.

```sh
cc -std=c11 -Wall -Wextra main.c -o q6
./q6
```

The inner loop always makes `n(n-1)/2` comparisons, regardless of input order. Therefore both best-case and worst-case running time are `Theta(n^2)`.
