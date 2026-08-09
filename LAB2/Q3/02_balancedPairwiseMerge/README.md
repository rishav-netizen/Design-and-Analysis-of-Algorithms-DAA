# Q3(b) — Balanced Pairwise Merge

![Method](https://img.shields.io/badge/method-balanced%20merge-2563EB)
![Complexity](https://img.shields.io/badge/time-%CE%98(nk%20log%20k)-059669)

[← Q3 overview](../README.md) · [Source code](main.c) · [Sequential method →](../01_sequentialMerge/README.md)

Instead of growing one result from left to right, split the array list into two halves. Recursively merge each half, then merge those two sorted answers.

```text
             merge all arrays
             /                \
       merge left half    merge right half
```

At one recursion level, at most `kn` elements are merged. There are `Θ(log k)` levels, so:

```text
T(k, n) = Θ(kn log k)
```

## Run

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o balanced_merge
./balanced_merge
```

The program asks for `k` and `n`, creates interleaved sorted inputs, and verifies the merged output.

The graph script uses this benchmark mode:

```bash
./balanced_merge --benchmark 16 8000 5
```

Compare its result with [sequential merge](../01_sequentialMerge/README.md), [the shared graph](../merge_k_arrays_complexity.png), and [raw benchmark data](../benchmark_results.csv).
