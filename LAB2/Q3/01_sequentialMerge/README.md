# Q3(a) — Sequential Merge

![Method](https://img.shields.io/badge/method-sequential%20merge-D97706)
![Complexity](https://img.shields.io/badge/time-%CE%98(nk%C2%B2)-C2410C)

[← Q3 overview](../README.md) · [Source code](main.c) · [Balanced method →](../02_balancedPairwiseMerge/README.md)

Start with the first sorted array. Merge it with the second array, merge that larger result with the third, and continue until all `k` arrays have been used.

```text
(((A₁ + A₂) + A₃) + ... + Aₖ)
```

The merge sizes are `2n, 3n, ..., kn`, so:

```text
T(k, n) = 2n + 3n + ... + kn = Θ(nk²)
```

## Run

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o sequential_merge
./sequential_merge
```

The program asks for `k` and `n`, generates interleaved sorted input arrays, prints a small result, and checks that it is sorted.

For the shared benchmark graph, the plotter calls this non-interactive mode:

```bash
./sequential_merge --benchmark 16 8000 5
```

It prints one CSV row. See [the Q3 benchmark plot](../merge_k_arrays_complexity.png) and [raw data](../benchmark_results.csv).
