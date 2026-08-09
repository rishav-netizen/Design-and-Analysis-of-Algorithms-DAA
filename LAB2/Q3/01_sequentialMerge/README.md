# 🟠 Q3(a) — Sequential Merge

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)
![Complexity](https://img.shields.io/badge/Time-%CE%98(nk%C2%B2)-D97706?style=for-the-badge)

</div>

> Merge one new sorted array into an ever-growing result. It is easy to follow, but repeatedly copying the growing result becomes costly.

[← Q3 overview](../README.md) · [Source code](main.c) · [Lab sheet (PDF)](../../2026_Week2_DAA_Lab_02.pdf) · [Balanced method →](../02_balancedPairwiseMerge/README.md)

**Tags:** `#C` `#Python` `#Git` `#GitHub` `#DAA` `#SequentialMerge` `#SortedArrays` `#Benchmarking` `#ComplexityAnalysis`

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
