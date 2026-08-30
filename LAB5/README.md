# Lab 05 - Selection Algorithms & Advanced Sorting

<div align="center">

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Progress](https://img.shields.io/badge/Progress-4%20of%204%20complete-059669?style=for-the-badge)

**Lab 05 · Week 5 · Design and Analysis of Algorithms**

</div>

> This lab explores order-statistic selection algorithms without sorting (Quickselect for finding median and $K$-th smallest element in expected linear time) and file-based advanced sorting algorithms (Quick Sort and Heap Sort) along with comprehensive asymptotic complexity analysis.

[← Repository home](../README.md) · [Questions sheet (Image)](questions.png)

```text
Lab 05  ████████████████████  100%  4 / 4 questions complete
```

| Question | Topic | Key Result | Files |
| :---: | --- | --- | --- |
| [Q1](Q1/README.md) | Find Median Without Sorting | Quickselect finds exact median in expected $\mathcal{O}(n)$ time without full array ordering | [C](Q1/main.c) · [README](Q1/README.md) |
| [Q2](Q2/README.md) | Find $K$'th Smallest Element | Hoare's Selection finds the $K$-th order statistic in expected $\mathcal{O}(n)$ time with $\mathcal{O}(1)$ space | [C](Q2/main.c) · [README](Q2/README.md) |
| [Q3](Q3/README.md) | Quick Sort of $N$ Elements via File I/O | Divide-and-conquer partition sorts $N$ random elements stored in file in $\mathcal{O}(n \log n)$ | [C](Q3/main.c) · [README](Q3/README.md) |
| [Q4](Q4/README.md) | Heap Sort of $N$ Elements via File I/O | Max-heap construction in $\mathcal{O}(n)$ + successive extractions guarantees $\mathcal{O}(n \log n)$ time | [C](Q4/main.c) · [README](Q4/README.md) |

## Supporting file

- [folders.py](folders.py) / [main.py](main.py): Directory setup and scaffolding script for Lab 5.

Each question README includes the detailed problem statement, algorithmic approach, time/space complexity analysis, build commands, and sample execution traces. Refer to [questions.png](questions.png) for the original lab assignment prompt.
