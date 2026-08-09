# 🔵 Q3(b) — Balanced Pairwise Merge

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)
![Complexity](https://img.shields.io/badge/Time-%CE%98(nk%20log%20k)-059669?style=for-the-badge)

</div>

> Divide the arrays into balanced halves, merge each half, and then merge those answers. This avoids repeatedly copying the same early arrays.

[← Q3 overview](../README.md) · [Source code](main.c) · [Lab sheet (PDF)](../../2026_Week2_DAA_Lab_02.pdf) · [Sequential method →](../01_sequentialMerge/README.md)

**Tags:** `#C` `#Python` `#Git` `#GitHub` `#DAA` `#BalancedMerge` `#DivideAndConquer` `#SortedArrays` `#Benchmarking` `#ComplexityAnalysis`

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
