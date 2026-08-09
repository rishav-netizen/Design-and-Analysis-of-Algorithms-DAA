# Design and Analysis of Algorithms

![Language](https://img.shields.io/badge/language-C%20%26%20Python-2563EB)
![Semester](https://img.shields.io/badge/semester-3-7C3AED)
![Labs](https://img.shields.io/badge/labs-2%20complete-059669)

Coursework for the Design and Analysis of Algorithms laboratory. Each question keeps its C program, supporting data/plotting code, results, and explanation together.

## Progress

```text
Lab 01  ████████████████████  100%  (6 / 6 questions)
Lab 02  ████████████████████  100%  (3 / 3 questions)
Overall ████████░░░░░░░░░░░░   2 / planned labs
```

## Labs

| Lab | Focus | Progress | Open |
| --- | --- | :---: | --- |
| 01 | Growth analysis, simulation, sorting, recursion and searching | `██████████ 100%` | [Lab 01 README](LAB1/README.md) |
| 02 | Dictionary implementations and merge algorithms | `██████████ 100%` | [Lab 02 README](LAB2/README.md) |

## Repository map

```text
DAA/
├── LAB1/                       Lab 01
│   └── README.md
├── LAB2/                       Lab 02
│   ├── Q1/                     Dictionary implementations and graph
│   ├── Q2/                     Two-way vs. three-way merge sort
│   └── Q3/                     Sequential vs. balanced k-array merge
└── README.md                   You are here
```

## Featured analysis

| Question | Algorithm comparison | Main files | Graph |
| --- | --- | --- | --- |
| [Lab 02 · Q2](LAB2/Q2/README.md) | `Θ(n log n)` two-way and three-way merge sort | [C program](LAB2/Q2/main.c) · [plotter](LAB2/Q2/plot_results.py) · [data](LAB2/Q2/data/benchmark_results.csv) | [PNG](LAB2/Q2/plots/merge_sort_complexity.png) |
| [Lab 02 · Q3](LAB2/Q3/README.md) | sequential `Θ(nk²)` vs. balanced `Θ(nk log k)` merge | [sequential C](LAB2/Q3/01_sequentialMerge/main.c) · [balanced C](LAB2/Q3/02_balancedPairwiseMerge/main.c) · [plotter](LAB2/Q3/plot_benchmarks.py) | [PNG](LAB2/Q3/merge_k_arrays_complexity.png) |

## Tools

- C11 with `cc`/GCC
- Python 3 for data collection and charts
- `matplotlib` for the benchmark figures

Run any program from the directory shown in its README. The question READMEs include exact commands and links to every related file.
