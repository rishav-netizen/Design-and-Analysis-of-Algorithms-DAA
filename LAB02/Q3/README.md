# 🧩 Q3 — Merging `k` Sorted Arrays

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)
![Benchmark](https://img.shields.io/badge/Benchmark-Verified-059669?style=for-the-badge)

</div>

> Given `k` sorted arrays with `n` elements each, combine them into one `kn`-element sorted array. This question compares a simple sequential approach with a balanced divide-and-conquer approach.

[← Q2](../Q2/README.md) · [Lab 02](../README.md) · [Lab sheet (PDF)](../2026_Week2_DAA_Lab_02.pdf) · [Repository home](../../README.md)

**Tags:** `#C` `#Python` `#Git` `#GitHub` `#DAA` `#MergeAlgorithms` `#DivideAndConquer` `#Benchmarking` `#ComplexityAnalysis`

## Methods and result

| Method | How it works | Worst-case time |
| --- | --- | --- |
| [1. Sequential merge](01_sequentialMerge/README.md) | Merge the growing result with the next array, one at a time. | `Θ(nk²)` |
| [2. Balanced pairwise merge](02_balancedPairwiseMerge/README.md) | Split the list of arrays into halves and merge the two answers. | `Θ(nk log k)` |

Sequential merging repeatedly copies the early arrays. Balanced merging processes at most `kn` elements per level and has `log₂ k` levels, so it scales better as `k` increases.

## Files

| File | What it does |
| --- | --- |
| [01_sequentialMerge/main.c](01_sequentialMerge/main.c) | Interactive program and CSV benchmark for Method 1. |
| [02_balancedPairwiseMerge/main.c](02_balancedPairwiseMerge/main.c) | Interactive program and CSV benchmark for Method 2. |
| [plot_benchmarks.py](plot_benchmarks.py) | Compiles both methods, verifies results, saves CSV data, and draws the graph. |
| [benchmark_results.csv](benchmark_results.csv) | Saved measurements from the supplied graph. |
| [merge_k_arrays_complexity.png](merge_k_arrays_complexity.png) | Runtime and normalized-growth comparison. |

## Run it

Try either program interactively:

```bash
cd 01_sequentialMerge
cc -std=c11 -Wall -Wextra -Werror main.c -o sequential_merge
./sequential_merge
```

```bash
cd ../02_balancedPairwiseMerge
cc -std=c11 -Wall -Wextra -Werror main.c -o balanced_merge
./balanced_merge
```

From this `Q3` folder, generate fresh data and the graph with:

```bash
python3 plot_benchmarks.py
```

For a faster check:

```bash
python3 plot_benchmarks.py --elements-per-array 2000 --trials 3 --k-values 2 4 8 16 32
```

## Graph

The left panel shows measured CPU time as `k` grows. The right panel divides each time by its expected growth term; a broadly flat line supports the complexity analysis.

![Sequential and balanced k-array merge benchmark](merge_k_arrays_complexity.png)
