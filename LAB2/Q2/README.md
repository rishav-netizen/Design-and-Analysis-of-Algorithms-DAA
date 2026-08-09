# Q2 — Two-Way vs. Three-Way Merge Sort

![Language](https://img.shields.io/badge/language-C-2563EB)
![Technique](https://img.shields.io/badge/technique-divide%20and%20conquer-7C3AED)
![Result](https://img.shields.io/badge/worst--case-%CE%98(n%20log%20n)-059669)

Compare normal merge sort, which splits the array into two pieces, with a modified version that splits it into three pieces. Both programs use the same random input and write average timings to a CSV file.

[← Lab 02](../README.md) · [Repository home](../../README.md) · [Next: Q3 →](../Q3/README.md)

## Result

| Method | Recurrence | Worst-case time | Extra space |
| --- | --- | --- | --- |
| Two-way merge sort | `T(n) = 2T(n/2) + Θ(n)` | `Θ(n log n)` | `Θ(n)` |
| Three-way merge sort | `T(n) = 3T(n/3) + Θ(n)` | `Θ(n log n)` | `Θ(n)` |

The three-way version has fewer recursive levels, but its merge compares three current values. The logarithm base only changes by a constant factor, so both algorithms are `Θ(n log n)`.

## Files

| File | What it does |
| --- | --- |
| [main.c](main.c) | Implements, checks, and benchmarks both merge sorts. |
| [plot_results.py](plot_results.py) | Turns the CSV timings into the graph below. |
| [data/benchmark_results.csv](data/benchmark_results.csv) | Saved benchmark measurements. |
| [plots/merge_sort_complexity.png](plots/merge_sort_complexity.png) | Generated two-panel comparison graph. |

## Build, run, and plot

```bash
cc -std=c11 -Wall -Wextra -Werror main.c -o merge_sort
./merge_sort
python3 plot_results.py
```

The default benchmark uses sizes `256` to `262144` and seven trials each. To use a smaller run or save a different CSV:

```bash
./merge_sort 65536 5 data/my_results.csv
python3 plot_results.py --input data/my_results.csv --output plots/my_results.png
```

`matplotlib` is required only for plotting: `python3 -m pip install matplotlib`.

## Graph

The left panel shows measured CPU time. The right panel divides time by `n log₂ n`; roughly level curves support the predicted growth. Timings naturally vary by computer and background load.

![Two-way and three-way merge-sort benchmark](plots/merge_sort_complexity.png)
